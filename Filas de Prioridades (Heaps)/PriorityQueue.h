#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdexcept>
#include <vector>

template <typename T>
class PriorityQueue{
    private: 
        std::vector<T> m_queue;
        size_t m_size;

        void move_up(size_t i) {
            while (i > 1 && m_queue[i/2] < m_queue[i]) {
                T aux = m_queue[i];
                m_queue[i] = m_queue[i/2];
                m_queue[i/2] = aux;
                i = i/2;
            }
        }
        void move_down(size_t i) {
            while (2*i <= m_size) {
                int l = 2*i;
                int r = 2*i + 1;
                int largest = i;
                if (m_queue[l] > m_queue[largest]) {
                    largest = l;
                } 
                if (r <= m_size && m_queue[r] > m_queue[largest]) {
                    largest = r;
                }
                if (largest != i) {
                    T aux = m_queue[i];
                    m_queue[i] = m_queue[largest];
                    m_queue[largest] = aux;
                    i = largest;
                } else {
                    break;
                }
            }
        }
        void build_max_heap() {
            for (size_t i = m_size / 2; i > 1; i--) {
                move_down(i);
            }
        }
    public:
        // constructor
        PriorityQueue() {
            m_size = 0;
        }
        PriorityQueue(const std::vector<T>& v) {
            m_size = v.size();
            m_queue.resize(m_size);
            for (size_t i = 0; i < m_size; i++) {
                m_queue[i+1] = v[i];
            }
            build_max_heap();
        }

        const T& top() const {
            if (m_size == 0) {
                throw std::out_of_range("PriorityQueue::top() : empty queue");
            }
            return m_queue[1];
        }
};

#endif