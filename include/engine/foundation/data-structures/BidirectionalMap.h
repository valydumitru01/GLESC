#include <unordered_map>
#include <utility>
#include <stdexcept>

template <typename Key, typename Value>
class BidirectionalMap {
public:
    bool insert(const Key &key, const Value &value) {
        if (keyToValue.count(key) || valueToKey.count(value)) {
            return false; // The key or the value already exists.
        }
        
        keyToValue[key] = value;
        valueToKey[value] = key;
        return true;
    }
    
    [[nodiscard]] const Key &getKey(const Value &value) const {
        auto it = valueToKey.find(value);
        if (it != valueToKey.end()) {
            return it->second;
        }
        throw std::runtime_error("Value not found in the map.");
    }
    
    [[nodiscard]] const Value &getValue(const Key &key) const {
        auto it = keyToValue.find(key);
        if (it != keyToValue.end()) {
            return it->second;
        }
        throw std::runtime_error("Key not found in the map.");
    }
    
    bool eraseByKey(const Key &key) {
        auto it = keyToValue.find(key);
        if (it != keyToValue.end()) {
            valueToKey.erase(it->second);
            keyToValue.erase(it);
            return true;
        }
        return false;
    }
    
    bool eraseByValue(const Value &value) {
        auto it = valueToKey.find(value);
        if (it != valueToKey.end()) {
            keyToValue.erase(it->second);
            valueToKey.erase(it);
            return true;
        }
        return false;
    }
    
    [[nodiscard]] bool containsKey(const Key &key) const {
        return keyToValue.count(key) > 0;
    }
    
    [[nodiscard]] bool containsValue(const Value &value) const {
        return valueToKey.count(value) > 0;
    }
    
    [[nodiscard]] size_t size() const {
        return keyToValue.size();
    }
    
    [[nodiscard]] bool empty() const {
        return keyToValue.empty();
    }
    
    void clear() {
        keyToValue.clear();
        valueToKey.clear();
    }

private:
    std::unordered_map <Key, Value> keyToValue;
    std::unordered_map <Value, Key> valueToKey;
};