#include "engine/foundation/logger/ILogger.h"

class FileLogger : public ILogger
{
public:
    FileLogger();

    void log(const std::string &text) override;

    void error(const std::string &text) override;
    
    void warning(const std::string &text) override;
    
    void info(const std::string &text) override;
    
    void infoBlue(const std::string &text) override;
    
    void infoPurple(const std::string &text) override;

    void importantInfo(const std::string &text) override;

    void importantInfoBlue(const std::string &text) override;
    
    void importantInfoPurple(const std::string &text) override;
    
    void success(const std::string &text) override;
};