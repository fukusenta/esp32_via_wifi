/**
 * @file  WiFiInfoManager.cpp
 * @brief Declaration of the AP connection settings manage class.
 *
 * This class offers manage information required to connect to a Wi-Fi AP,
 * retained even after power is lost.
 *
 * @author  Kusakari
 * @note    2024.03.31 - Created.
 */
#include "WiFiInfoManager.h"

namespace viawifi {   // Namespace definition

/**
 * @brief Retreves or configure the SSID and password.
 * @param ap_ssid The SSID for operating as an AP.
 * @param ap_password The password for operating as an AP.
 * @param is_config A flag to force the configuration.
 * @return Whether the configuration is complete (true for ready, false for reboot).
 */
const bool WiFiInfoManager::configure(const char* ap_ssid, const char* ap_password, const bool is_config) {
  // Retreves existing configurations.
  this->setAPConfig(ap_ssid, ap_password);
  this->setClientConfig("", "");
  if(!this->restore()) return false;

  // Check if the configurations is complete.
  if(!is_config) {
    if(this->isReady()) return true;
  }
  
  // Runs a web server to accept input from users.
  if(this->get()) this->store();
  return false;
}

/**
 * @brief Gets the SSID for operating as an AP.
 * @return The SSID for operating as an AP.
 */
const char* WiFiInfoManager::getAPSSID() {
  return this->ap_config.ssid;
}
/**
 * @brief Gets the password for operating as an AP.
 * @return The password for operating as an AP.
 */
const char* WiFiInfoManager::getAPPassword() {
  return this->ap_config.password;
}
/**
 * @brief Gets the SSID for connection.
 * @return The SSID for connection.
 */
const char* WiFiInfoManager::getSSID() {
  return this->client_config.ssid;
}
/**
 * @brief Gets the password for connection.
 * @return The password for connection.
 */
const char* WiFiInfoManager::getPassword() {
  return this->client_config.password;
}


/**
 * @brief Declares EEPROM area.
 * @return Whether EEPROM initialization was successful.
 */
const bool WiFiInfoManager::init() {
  this->is_enable = EEPROM.begin(this->EEPROM_SIZE);
  return this->is_enable;
}
/**
 * @brief Restore the client configurations from EEPROM area.
 * @return Whether the restore from EEPROM was successful.
 */
const bool WiFiInfoManager::restore() {
  if(!this->is_enable) {
    if(!this->init()) return false;
  }

  wifi_info buf;
  EEPROM.get<wifi_info>(0, buf);
  if(buf.ssid[0] != 0xFF) strcpy(this->client_config.ssid, buf.ssid);
  if(buf.password[0] != 0xFF) strcpy(this->client_config.password, buf.password);
  return true;
}
/**
 * @brief Store the client configurations to EEPROM area.
 * @return Whether the store to EEPROM was successful.
 */
const bool WiFiInfoManager::store() {
  if(!this->is_enable) {
    if(!this->init()) return false;
  }

  EEPROM.put<wifi_info>(0, this->client_config);
  EEPROM.commit();
  return true;
}

/**
 * @brief Store the AP configurations in memory.
 * @param ap_ssid The SSID for operating as an AP.
 * @param ap_password The password for operating as an AP.
 */
void WiFiInfoManager::setAPConfig(const char* ap_ssid, const char* ap_password) {
  strcpy(this->ap_config.ssid, ap_ssid);
  strcpy(this->ap_config.password, ap_password);
}
/**
 * @brief Store the client configurations in memory.
 * @param ssid The SSID for connection.
 * @param password The password for connection.
 */
void WiFiInfoManager::setClientConfig(const char* ssid, const char* password){
  strcpy(this->client_config.ssid, ssid);
  strcpy(this->client_config.password, password);
}

/**
 * @brief Is connectable.
 * @return Whether has the configurations required for connection.
 */
const bool WiFiInfoManager::isReady() {
  return strcmp(this->client_config.ssid, "") != 0;
}
/**
 * @brief Runs the web server, to get the SSID and password.
 * @return Has been changes (ture for store the changes, false for discard).
 */
const bool WiFiInfoManager::get() {
  //
  // hogehoge
  //
  return false;
}

} // Namespace viawifi end