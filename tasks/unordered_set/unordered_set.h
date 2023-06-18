#pragma once

#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : n_elements_(0), data_() {
    }
    explicit UnorderedSet(size_t count) : n_elements_(0), data_(count) {
    }
    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : n_elements_(0), data_() {
        for (auto i = first; i != last; ++i) {
            Insert(*i);
        }
    }
    UnorderedSet(const UnorderedSet& other) : n_elements_(other.n_elements_), data_(other.data_.size()) {
        for (size_t i = 0; i < data_.size(); ++i) {
            data_[i] = std::list<KeyT>(other.data_[i]);
        }
    }
    UnorderedSet(UnorderedSet&& other) {
        n_elements_ = std::move(other.n_elements_);
        data_ = std::move(other.data_);
        other.n_elements_ = 0;
        other.data_ = std::vector<std::list<KeyT>>(0);
    }
    ~UnorderedSet() = default;
    UnorderedSet& operator=(const UnorderedSet& other) {
        n_elements_ = other.n_elements_;
        data_ = std::vector<std::list<KeyT>>(other.data_.size());
        for (size_t i = 0; i < data_.size(); ++i) {
            data_[i] = std::list<KeyT>(other.data_[i]);
        }
        return *this;
    }
    UnorderedSet& operator=(UnorderedSet&& other) {
        n_elements_ = std::move(other.n_elements_);
        data_ = std::move(other.data_);
        other.n_elements_ = 0;
        other.data_ = std::vector<std::list<KeyT>>(0);
        return *this;
    }
    size_t Size() const {
        return n_elements_;
    }
    bool Empty() const {
        return n_elements_ == 0;
    }
    void Clear() {
        data_.clear();
        n_elements_ = 0;
    }
    void Insert(const KeyT& key) {
        if (Find(key)) {
            return;
        }
        if (Size() == 0 && BucketCount() == 0) {
            Reserve(1);
        } else if (Size() == BucketCount()) {
            Reserve(2 * BucketCount());
        }
        data_[std::hash<KeyT>{}(key) % BucketCount()].emplace_back(key);
        ++n_elements_;
    }
    void Insert(KeyT&& key) {
        if (Find(key)) {
            return;
        }
        if (Size() == 0 && BucketCount() == 0) {
            Reserve(1);
        } else if (Size() == BucketCount()) {
            Reserve(2 * BucketCount());
        }
        data_[std::hash<KeyT>{}(key) % BucketCount()].emplace_back(std::move(key));
        ++n_elements_;
    }
    void Erase(const KeyT& key) {
        if (!Find(key)) {
            return;
        }
        for (auto i = data_[std::hash<KeyT>{}(key) % BucketCount()].begin();
             i != data_[std::hash<KeyT>{}(key) % BucketCount()].end(); ++i) {
            if (*i == key) {
                data_[std::hash<KeyT>{}(key) % BucketCount()].erase(i);
                --n_elements_;
                break;
            }
        }
    }
    bool Find(const KeyT& key) const {
        if (Size() == 0) {
            return false;
        }
        for (auto i = data_[std::hash<KeyT>{}(key) % BucketCount()].begin();
             i != data_[std::hash<KeyT>{}(key) % BucketCount()].end(); ++i) {
            if (*i == key) {
                return true;
            }
        }
        return false;
    }
    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count == BucketCount()) {
            return;
        }
        if (new_bucket_count < Size()) {
            return;
        }
        auto old_data = data_;
        data_ = std::vector<std::list<KeyT>>(new_bucket_count);
        n_elements_ = 0;
        for (const auto& chain : old_data) {
            for (auto elem : chain) {
                Insert(elem);
            }
        }
    }
    void Reserve(size_t new_bucket_count) {
        if (new_bucket_count <= BucketCount()) {
            return;
        }
        auto old_data = data_;
        data_ = std::vector<std::list<KeyT>>(new_bucket_count);
        n_elements_ = 0;
        for (const auto& chain : old_data) {
            for (auto elem : chain) {
                Insert(elem);
            }
        }
    }
    size_t BucketCount() const {
        return data_.size();
    }
    size_t BucketSize(size_t id) const {
        if (id >= data_.size()) {
            return 0;
        }
        return data_[id].size();
    }
    size_t Bucket(const KeyT& key) const {
        return std::hash<KeyT>{}(key) % BucketCount();
    }
    double LoadFactor() const {
        if (BucketCount() == 0) {
            return 0;
        }
        return n_elements_ / static_cast<double>(BucketCount());
    }

private:
    size_t n_elements_;
    std::vector<std::list<KeyT>> data_;
};
