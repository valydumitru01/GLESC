#include <string>
#include <memory>
#include <vector>
#include "ILogger.h"
//Include loggers
#include "concrete-loggers/TerminalLogger.h"
#include "concrete-loggers/FileLogger.h"


class Logger : public ILogger{
public:
    Logger();

    void executeOnAllInputs(void (ILogger::*func)(const std::string&), const std::string &text);

    static Logger& get();

    void addLogger(std::unique_ptr<ILogger> loggerParam);

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
private:
    std::vector<std::unique_ptr<ILogger>> loggers;
    static Logger logger;
};

