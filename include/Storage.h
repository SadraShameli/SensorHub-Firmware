#pragma once
#include "Backend.h"

class Storage
{
public:
    static void MountSPIFFS(const char *, const char *);
    static void Init();
    static void Commit();
    static void Reset();

    static const std::string &GetSSID() { return m_SSID; }
    static const std::string &GetPassword() { return m_Password; }
    static const std::string &GetAddress() { return m_Address; }
    static const std::string &GetAuthKey() { return m_AuthKey; }
    static const std::string &GetDeviceName() { return m_DeviceName; }
    static Backend::DeviceTypes GetDeviceType() { return (Backend::DeviceTypes)m_StorageData.DeviceType; }
    static uint32_t GetDeviceId() { return m_StorageData.DeviceId; }
    static uint32_t GetLoudnessThreshold() { return m_StorageData.LoudnessThreshold; }
    static uint32_t GetRegisterInterval() { return m_StorageData.RegisterInterval; }
    static bool GetEnabledSensors(Backend::SensorTypes sensor) { return m_StorageData.Sensors[sensor - 1]; }
    static bool GetConfigMode() { return m_StorageData.ConfigMode; };

    static void SetSSID(const std::string &str) { m_SSID = str; }
    static void SetPassword(const std::string &str) { m_Password = str; }
    static void SetAddress(const std::string &str) { m_Address = str; }
    static void SetAuthKey(const std::string &str) { m_AuthKey = str; }
    static void SetDeviceName(const std::string &str) { m_DeviceName = str; }
    static void SetDeviceType(Backend::DeviceTypes type) { m_StorageData.DeviceType = (uint32_t)type; }
    static void SetDeviceId(uint32_t num) { m_StorageData.DeviceId = num; }
    static void SetLoudnessThreshold(uint32_t num) { m_StorageData.LoudnessThreshold = num; }
    static void SetRegisterInterval(uint32_t num) { m_StorageData.RegisterInterval = num; }
    static void SetEnabledSensors(Backend::SensorTypes sensor, bool state) { m_StorageData.Sensors[sensor - 1] = state; }
    static void SetConfigMode(bool config) { m_StorageData.ConfigMode = config; }

private:
    static constexpr int SSIDLength = 33, PasswordLength = 65, UUIDLength = 37, EndpointLength = 241;
    struct StorageData
    {
        uint32_t SSID[SSIDLength];
        uint32_t Password[PasswordLength];
        uint32_t Address[EndpointLength];
        uint32_t AuthKey[UUIDLength];
        uint32_t DeviceName[UUIDLength];
        uint32_t DeviceType;
        uint32_t DeviceId;
        uint32_t LoudnessThreshold;
        uint32_t RegisterInterval;
        bool Sensors[Backend::SensorTypes::SensorCount - 1];
        bool ConfigMode;
    };

    static void CalculateMask();
    static void EncryptText(uint32_t *, const std::string &);
    static void DecryptText(uint32_t *, std::string &);

    inline static uint32_t m_EncryptionMask = 0;
    inline static StorageData m_StorageData = {};
    inline static std::string m_SSID, m_Password, m_DeviceName, m_Address, m_AuthKey;
};