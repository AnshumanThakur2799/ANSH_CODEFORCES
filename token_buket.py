import time
import threading

class TokenBucket:
    def __init__(self, capacity, refill_rate):
        self.capacity = capacity      # Maximum number of tokens the bucket can hold
        self.tokens = capacity        # Current number of tokens in the bucket
        self.refill_rate = refill_rate  # Rate at which tokens are added to the bucket (tokens per second)
        self.last_refill_time = time.time()  # Last time tokens were added
        self.lock = threading.Lock()  # Mutex to make the class thread-safe

    def refill(self):
        now = time.time()
        duration = now - self.last_refill_time
        new_tokens = duration * self.refill_rate
        self.tokens = min(self.capacity, self.tokens + new_tokens)
        self.last_refill_time = now

    def consume(self, amount):
        with self.lock:
            self.refill()
            if self.tokens >= amount:
                self.tokens -= amount
                return True
            return False

    def get_tokens(self):
        with self.lock:
            self.refill()
            return self.tokens

if __name__ == "__main__":
    # Example usage of the TokenBucket
    bucket = TokenBucket(10, 1)  # Capacity of 10 tokens and refill rate of 1 token per second

    for i in range(30):
        if bucket.consume(4):
            print(f"Request {i + 1}: Allowed")
        else:
            print(f"Request {i + 1}: Denied")
        time.sleep(1)  # Simulate time delay
