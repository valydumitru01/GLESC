#include "engine/foundation/logger/ILogger.h"
#include <fstream>

class FileLogger : public ILogger
{
private:
    std::ofstream logFile;

public:
    FileLogger() {
        // Open the log file in append mode
        logFile.open("log.txt", std::ios::app);
    }
    
    ~FileLogger() {
        if(logFile.is_open()) {
            logFile.close();
        }
    }
    
    void log(const std::string &text) override {
        logFile << "[LOG] " << text << std::endl;
    }
    
    void error(const std::string &text) override {
        logFile << "[ERROR] " << text << std::endl;
    }
    
    void warning(const std::string &text) override {
        logFile << "[WARNING] " << text << std::endl;
    }
    
    void info(const std::string &text) override {
        logFile << "[INFO] " << text << std::endl;
    }
    
    void infoBlue(const std::string &text) override {
        logFile << "[INFO Blue] " << text << std::endl;
    }
    
    void infoPurple(const std::string &text) override {
        logFile << "[INFO Purple] " << text << std::endl;
    }
    
    void importantInfo(const std::string &text) override {
        logFile << "[IMPORTANT INFO] " << text << std::endl;
    }
    
    void importantInfoBlue(const std::string &text) override {
        logFile << "[IMPORTANT INFO Blue] " << text << std::endl;
    }
    
    void importantInfoPurple(const std::string &text) override {
        logFile << "[IMPORTANT INFO Purple] " << text << std::endl;
    }
    
    void success(const std::string &text) override {
        logFile << "[SUCCESS] " << text << std::endl;
    }
};