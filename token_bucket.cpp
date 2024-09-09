#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

class TokenBucket {
private:
    double capacity;       // Maximum number of tokens the bucket can hold
    double tokens;         // Current number of tokens in the bucket
    double refillRate;     // Rate at which tokens are added to the bucket (tokens per second)
    std::chrono::steady_clock::time_point lastRefillTime;  // Last time tokens were added
    std::mutex mtx;        // Mutex to make the class thread-safe

    void refill() {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = now - lastRefillTime;
        double newTokens = duration.count() * refillRate;
        tokens = std::min(capacity, tokens + newTokens);
        lastRefillTime = now;
    }

public:
    TokenBucket(double capacity, double refillRate) 
        : capacity(capacity), tokens(capacity), refillRate(refillRate) {
        lastRefillTime = std::chrono::steady_clock::now();
    }

    bool consume(double amount) {
        std::lock_guard<std::mutex> lock(mtx);
        refill();
        if (tokens >= amount) {
            tokens -= amount;
            return true;
        }
        return false;
    }

    double getTokens() {
        std::lock_guard<std::mutex> lock(mtx);
        refill();
        return tokens;
    }
};

int main() {
    // Example usage of the TokenBucket
    TokenBucket bucket(10, 1);  // Capacity of 10 tokens and refill rate of 1 token per second

    for (int i = 0; i < 15; ++i) {
        if (bucket.consume(4)) {
            std::cout << "Request " << i + 1 << ": Allowed\n";
        } else {
            std::cout << "Request " << i + 1 << ": Denied\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate time delay
    }

    return 0;
}
