#include <iostream>
#include <unordered_map>
#include <deque>
#include <fstream>

using namespace std;

// BaseCache is a pure virtual class wich basic cache operations
class BaseCache {
public:
	virtual bool has(const string& key) = 0;
	virtual string read(const string& key) = 0;
	virtual void write(const string& key, const string& value) = 0;
	virtual void remove(const string& key) = 0;
};

// MemoryCache is a class that implements using memory as a cache
class MemoryCache : public BaseCache {
private:
    unordered_map<string, string> _cache;
public:
	bool has(const string& key) override {
		return _cache.find(key) != _cache.end();
	}
	
	string read(const string& key) override {
		if (has(key)) {
			return _cache[key];
		}
		return "";
	}
	
	void write(const string& key, const string& value) override {
		_cache[key] = value;
	}
	
	void remove(const string& key) override {
		_cache.erase(key);
	}
};

// NullCache is a class that implements cache interface without caching at all
class NullCache : public BaseCache {
public:
	bool has(const string& key) override {
		return false;
	}

	string read(const string& key) override {
		return "";
	}

	void write(const string& key, const string& value) override {
	}

	void remove(const string& key) override {
	}
};

// PoorManMemoryCache is a class that implements using memory as a cache with limited size
class PoorManMemoryCache : public BaseCache {
private:
	unordered_map<string, string>	_cache;		// cache data
	deque<string>					_last;		// last written keys
	const int						_max_size;	// max cache size

public:
	PoorManMemoryCache(int max_size) : _max_size(max_size) {
	}

	bool has(const string& key) override {
		return _cache.find(key) != _cache.end();
	}

	string read(const string& key) override {
		if (has(key)) {
			return _cache[key];
		}
		return "";
	}

	void write(const string& key, const string& value) override {
		_cache[key] = value;
		_last.push_back(key);

		// remove oldest written element if cache is full
		if (_last.size() > _max_size) {
			_cache.erase(_last.front());
			_last.pop_front();
		}
	}

	void remove(const string& key) override {
		if (_cache.erase(key) > 0) {
			for (auto it = _last.begin(); it != _last.end(); ++it) {
				if (*it == key) {
					_last.erase(it);
					break;
				}
			}
		}
	}
};

class FileCache : public BaseCache {
private:
	const int _fcount;

	unordered_map<string, string> load_bucket(const string& key) {
		unordered_map<string, string> data;

		char fname[0x20];
		sprintf_s(fname, "%08X.cache", int(hash<string>{}(key) % _fcount));

		ifstream file(fname);
		string	k, v;
		while (file >> k >> v) {
			data[k] = v;
		}

		return data;
	}

	void save_bucket(const string& key, unordered_map<string, string> const& data) {
		char fname[0x20];
		sprintf_s(fname, "%08X.cache", int(hash<string>{}(key) % _fcount));

		ofstream file(fname);

		for (auto const& kv : data) {
			file << kv.first << "\t" << kv.second << endl;
		}
	}

public:
	FileCache(const int fcount) : _fcount(fcount) {
	}

	bool has(const string& key) override {
		auto data = load_bucket(key);
		return data.find(key) != data.end();
	}

	string read(const string& key) override {
		auto data = load_bucket(key);

		if (data.find(key) != data.end()) {
			return data[key];
		}

		return "";
	}

	void write(const string& key, const string& value) override {
		auto data = load_bucket(key);
		data[key] = value;
		save_bucket(key, data);
	}

	void remove(const string& key) override {
		auto data = load_bucket(key);
		if (data.erase(key) > 0) {
			save_bucket(key, data);
		}
	}
};

class CacheApplier {
private:
	BaseCache* _strategy;

public:
	void set_strategy(BaseCache& strategy) {
		_strategy = &strategy;
	}

	string read_from_cache(const string& key) {
		return _strategy->read(key);
	}

	void write_from_cache(const string& key, const string& value) {
		_strategy->write(key, value);
	}

	void delete_from_cache(const string& key) {
		_strategy->remove(key);
	}
};

int main() {

	vector<pair<string, string>> data = {
		{ "key1", "value1" },
		{ "key2", "value2" },
		{ "key3", "value3" },
		{ "key2", "value2" },
		{ "key4", "value4" },
		{ "key3", "value3" },
		{ "key1", "value1" },
	};

	// MemoryCache		cache;
	// NullCache		cache;
	// PoorManMemoryCache	cache(2);
	FileCache			cache(2);
	CacheApplier		applier;

	applier.set_strategy(cache);

	for (auto const& kv : data) {
		if (!applier.read_from_cache(kv.first).empty()) {
			cout << "Key: " << kv.first << " Value: " << applier.read_from_cache(kv.first) << " was found in cache" << endl;
		} else {
			cout << "Key: " << kv.first << " Value: " << kv.second << " was added to cache" << endl;
			applier.write_from_cache(kv.first, kv.second);
		}
	}
}

