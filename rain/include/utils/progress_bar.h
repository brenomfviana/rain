#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include <iostream>
#include <string>
#include <mutex>

namespace utils {

    class ProgressBar {

        private:
            // Bar width
            size_t barWidth;
            // Max value
            unsigned int max;
            // Current value
            unsigned int value;
            // Current percentage
            float percent;
            // Mutex
            std::mutex mtx;

            /*!
             * Print progress bar.
             */
            void print() {
                std::string bar;
                // Calculates progress
                for (unsigned int i = 0; i < barWidth; i++) {
                    if (i < (unsigned int) ((percent * barWidth) / 100.f)) {
                        bar.replace(i, 1, "=");
                    } else if (i == (unsigned int) ((percent * barWidth) / 100.f)) {
                        bar.replace(i, 1, ">");
                    } else {
                        bar.replace(i, 1, " ");
                    }
                }
                // Print
                std::cout << "\r" "|" << bar << "| ";
                std::cout.width(3);
                std::cout << ((int) percent) << "%" << std::flush;
            }

        public:
            /*!
             * Progress bar constructor.
             *
             * @param sz Bar width
             * @param max Max value
             */
            ProgressBar(size_t sz = 50, unsigned int max = 100) :
                barWidth(sz), max(max), value(0) { /* empty */ }

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
                float p = ((value * 100.f) / (max * 1.f));
                // Check if needs to update progress bar
                if (p > percent) {
                    percent = p;
                    print();
                }
                mtx.unlock();
            }
    };

} // namespace utils

#endif /* _PROGRESS_BAR_H_ */
