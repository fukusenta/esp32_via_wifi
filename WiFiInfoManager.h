/**
 * @file  WiFiInfoManager.h
 * @brief Declaration of the AP connection settings manage class.
 *
 * This class offers manage information required to connect to a Wi-Fi AP,
 * retained even after power is lost.
 *
 * @author  Kusakari
 * @note    2024.03.31 - Created.
 */
#ifndef WIFI_INFO_MANAGER_H  // Include guard start
#define WIFI_INFO_MANAGER_H

#include <cstring>
#include "EEPROM.h"
#include "Arduino.h"  // keep

namespace viawifi { // Namespace definition

/**
 * @class WiFiInfoManager
 * @brief Manages Wi-Fi access point connection details.

 */
class WiFiInfoManager {
  /**
   * @struct wifi_info
   * @brief Structure consolidating Wi-Fi configurations.
   */
  struct wifi_info {
    char ssid[33];      // Wi-Fi SSID, 2 to 32 characters (+1 for '\0').
    char password[64];  // Wi-Fi password, 8 to 63 characters (+1 for '\0').
  };

  private:
    static constexpr int const EEPROM_SIZE = 97;
    wifi_info ap_config;      // for as an AP.
    wifi_info client_config;  // for as a client.
    bool is_enable = false;   // A flag to use EEPROM area.

    /**
     * @brief Declares EEPROM area.
     * @return Whether EEPROM initialization was successful.
     */
    const bool init();
    /**
     * @brief Restore the client configurations from EEPROM area.
     * @return Whether the restore from EEPROM was successful.
     */
    const bool restore();
    /**
     * @brief Store the client configurations to EEPROM area.
     * @return Whether the store to EEPROM was successful.
     */
    const bool store();

    /**
     * @brief Store the AP configurations in memory.
     * @param ap_ssid The SSID for operating as an AP.
     * @param ap_password The password for operating as an AP.
     */
    void setAPConfig(const char* ap_ssid, const char* ap_password);
    /**
     * @brief Store the client configurations in memory.
     * @param ssid The SSID for connection.
     * @param password The password for connection.
     */
    void setClientConfig(const char* ssid, const char* password);

    /**
     * @brief Is connectable.
     * @return Whether has the configurations required for connection.
     */
    const bool isReady();
    /**
     * @brief Runs the web server, to get the SSID and password.
     * @return Has been changes (ture for store the changes, false for discard).
     */
    const bool get();

  public:
    /**
     * @brief Constructor for this manager.
     */
    WiFiInfoManager() = default;

    /**
     * @brief Retreves or configure the SSID and password.
     * @param ap_ssid The SSID for operating as an AP.
     * @param ap_password The password for operating as an AP.
     * @param is_config A flag to force the configuration.
     * @return Whether the configuration is complete (true for ready, false for reboot).
     */
    const bool configure(const char* ap_ssid, const char* ap_password, const bool is_config);

    /**
     * @brief Gets the SSID for operating as an AP.
     * @return The SSID for operating as an AP.
     */
    const char* getAPSSID();
    /**
     * @brief Gets the password for operating as an AP.
     * @return The password for operating as an AP.
     */
    const char* getAPPassword();
    /**
     * @brief Gets the SSID for connection.
     * @return The SSID for connection.
     */
    const char* getSSID();
    /**
     * @brief Gets the password for connection.
     * @return The password for connection.
     */
    const char* getPassword();
};

} // Namespace viawifi end

#endif  // !WIFI_INFO_MANAGER_H