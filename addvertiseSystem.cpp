#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <random>

// Advertisement class representing an ad
class Advertisement {
private:
    std::string message;
    bool blinkingText;

public:
    Advertisement(const std::string& msg, bool blink) : message(msg), blinkingText(blink) {}

    std::string getMessage() const {
        return message;
    }

    bool isBlinkingText() const {
        return blinkingText;
    }
};

// Customer class representing a customer
class Customer {
private:
    std::string name;
    int payment;
    std::vector<Advertisement> ads;

public:
    Customer(const std::string& nm, int pay) : name(nm), payment(pay) {}

    void addAdvertisement(const Advertisement& ad) {
        ads.push_back(ad);
    }

    int getPayment() const {
        return payment;
    }

    Advertisement getRandomAd() const {
        if (ads.empty()) {
            return Advertisement("", false); // Return an empty ad if no ads are available
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, static_cast<int>(ads.size()) - 1);

        int index = dis(gen);
        return ads[index];
    }
};

int main() {
    // Create customers and their ads
    Customer hederligeHarrys("Hederlige Harrys Cars", 5000);
    hederligeHarrys.addAdvertisement(Advertisement("Köp bil hos Harry", false));
    hederligeHarrys.addAdvertisement(Advertisement("En god bilaffär (för Harry!)", false));
    hederligeHarrys.addAdvertisement(Advertisement("Hederlige Harrys Bilar", true));

    // ... (similarly create other customers and their ads)

    // Define the list of customers
    std::vector<Customer> customers = {hederligeHarrys /*, other customers...*/};

    unsigned int tick = 0; // Milliseconds since start

    while (true) {
        // Simulate showing an ad for 20 seconds (20000 milliseconds)
        if (tick % 20000 == 0) {
            // Randomly select a customer
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, static_cast<int>(customers.size()) - 1);

            int customerIndex = dis(gen);
            Customer selectedCustomer = customers[customerIndex];

            // Get a random ad from the selected customer
            Advertisement randomAd = selectedCustomer.getRandomAd();

            // Display the selected ad
            std::cout << "Selected Customer: " << selectedCustomer.getPayment() << " kr Payment" << std::endl;
            std::cout << "Selected Ad: " << randomAd.getMessage() << std::endl;
            std::cout << "Blinking Text: " << (randomAd.isBlinkingText() ? "Yes" : "No") << std::endl;

            // Sleep for 20 seconds (simulate ad display time)
            std::this_thread::sleep_for(std::chrono::milliseconds(20000));
        }

        // Increment tick by 100 milliseconds (simulating passage of time)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tick += 100;
    }

    return 0;
}
