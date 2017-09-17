#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include <iostream>
#include <string>
#include <mutex>

namespace utils {

    class ProgressBar {

        private:
            // Bar width
            size_t bar_width;
            // Max value
            unsigned int max;
            // Current value
            unsigned int value;
            // Current percentage
            float percent;
            // Mutex
            std::mutex mtx;

            /*!
             * .
             */
            void print() {
                std::string bar;

                for (unsigned int i = 0; i < bar_width; i++) {
                    if (i < (unsigned int) (percent / 2)) {
                        bar.replace(i, 1, "=");
                    } else if (i == (unsigned int) (percent / 2)) {
                        bar.replace(i, 1, ">");
                    } else {
                        bar.replace(i, 1, " ");
                    }
                }
                std::cout << "\r" "|" << bar << "| ";
                std::cout.width(3);
                std::cout << ((int) percent) << "%" << std::flush;
            }

        public:
            /*!
             * Progress bar constructor.
             *
             * @param sz_ Bar width
             * @param max_ Max value
             */
            ProgressBar(size_t sz_ = 50, unsigned int max_ = 100) : bar_width(sz_),
                max(max_), value(0) { /* empty */ }

            /*!
             * Progress bar destructor.
             */
            ~ProgressBar() { /* empty */ }

            /*!
             * Increase value of progress bar.
             */
            inline void increase() {
                mtx.lock();
                value++;
                // Calculates percentage
                float _percent = ((value * 1.f) / (max * 1.f)) * 100;
                // Check if needs to update progress bar
                if (_percent > percent) {
                    percent = _percent;
                    print();
                }
                mtx.unlock();
            }
    };

} // namespace utils

#endif /* _PROGRESS_BAR_H_ */
