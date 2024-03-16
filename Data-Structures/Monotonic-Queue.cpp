template <typename T>
struct minimum_queue {
    stack<pair<T,T>> s2, s1; //---(s2----||s1---)---
    //add new elements to s1, remove elements from s2
    minimum_queue() {
        s1 = stack<pair<T,T>>();
        s2 = stack<pair<T,T>>();
    }

    T getMinimum() {
        T minimum;
        if (s1.empty() || s2.empty())
            minimum = s1.empty() ? s2.top().second : s1.top().second;
        else
            minimum = min(s1.top().second, s2.top().second);
        return minimum;
    }
    
    void push(T new_element) {
        T minimum = s1.empty() ? new_element : min(new_element, s1.top().second);
        s1.push({new_element, minimum});
    }
    
    void pop() {
        if (s2.empty()) {
            assert(!s1.empty());
            while (!s1.empty()) {
                T element = s1.top().first;
                s1.pop();
                T minimum = s2.empty() ? element : min(element, s2.top().second);
                s2.push({element, minimum});
            }
        }
        s2.pop();
    }
};