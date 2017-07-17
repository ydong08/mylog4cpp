
// Module:  Log4CPLUS
// File:    logger.h


#ifndef LOG4CPLUS_LOGGERHEADER_
#define LOG4CPLUS_LOGGERHEADER_

#include "log4cplus/platform.h"
#include "log4cplus/loglevel.h"
#include "log4cplus/appenderattachable.h"
#include "log4cplus/loggerfactory.h"

#include <vector>

namespace log4cplus
{


class Appender;
class Hierarchy;
class HierarchyLocker;
class DefaultLoggerFactory;
class LoggerImpl;


/** \typedef vector<Logger> LoggerList
* This is a list of {@link Logger Loggers}. */
typedef std::vector<Logger> LoggerList;


/**
* This is the central class in the log4cplus package. One of the
* distintive features of log4cplus are hierarchical loggers and their
* evaluation.
* 
* See the <a href="../../../../manual.html">user manual</a> for an
* introduction on this class.
*/
class LOG4CPLUS_EXPORT Logger : public log4cplus::AppenderAttachable
{
public:
	// Static Methods
	/**
	* Returns <code>true </code>if the named logger exists 
	* (in the default hierarchy).
	*                
	* @param name The name of the logger to search for.
	*/
	static bool exists(const std::string& name);

	/*
	* Returns all the currently defined loggers in the default
	* hierarchy.
	* 
	* The root logger is <em>not</em> included in the returned
	* list.      
	*/
	static LoggerList getCurrentLoggers();

	/**
	* Return the default Hierarchy instance.
	*/
	static Hierarchy& getDefaultHierarchy();

	/**
	* Retrieve a logger with name <code>name</code>.  If the named 
	* logger already exists, then the existing instance will be returned. 
	* Otherwise, a new instance is created. 
	* 
	* By default, loggers do not have a set LogLevel but inherit
	* it from the hierarchy. This is one of the central features of
	* log4cplus.
	* 
	* @param name The name of the logger to retrieve.  
	*/
	static Logger getInstance(const std::string& name);

	/**
	* Like getInstance() except that the type of logger
	* instantiated depends on the type returned by the {@link
	* LoggerFactory#makeNewLoggerInstance} method of the
	* <code>factory</code> parameter.
	*                          
	* This method is intended to be used by sub-classes.
	*                                   
	* @param name The name of the logger to retrieve.
	* @param factory A {@link LoggerFactory} implementation that will
	* actually create a new Instance.
	*/
	static Logger getInstance(const std::string& name, LoggerFactory& factory);

	/**
	* Return the root of the default logger hierrachy.
	* 
	* The root logger is always instantiated and available. It's
	* name is "root".
	* 
	* Nevertheless, calling {@link #getInstance
	* Logger.getInstance("root")} does not retrieve the root logger 
	* but a logger just under root named "root".
	*/
	static Logger getRoot();


	/**
	* Close all attached appenders implementing the AppenderAttachable
	* interface.  
	*/
	void closeNestedAppenders() const;

	/**
	* Check whether this logger is enabled for a given
	* LogLevel passed as parameter.
	*
	* @return boolean True if this logger is enabled for <code>ll</code>.
	*/
	bool isEnabledFor(LogLevel ll) const;

	void log(InternalLoggingEvent const&) const;

	/**
	* This method creates a new logging loggingEvent and logs the loggingEvent
	* without further checks.  
	*/
	void forcedLog(LogLevel ll, const std::string& message) const;

	void forcedLog(InternalLoggingEvent const&) const;

	/**
	* Call the appenders in the hierrachy starting at
	* <code>this</code>.  If no appenders could be found, emit a
	* warning.
	* 
	* This method calls all the appenders inherited from the
	* hierarchy circumventing any evaluation of whether to log or not
	* to log the particular log request.
	*
	* @param loggingEvent the loggingEvent to log.
	*/
	void callAppenders(const InternalLoggingEvent& loggingEvent) const;

	/**
	* Starting from this logger, search the logger hierarchy for a
	* "set" LogLevel and return it. Otherwise, return the LogLevel of the
	* root logger.
	* 
	* The Logger class is designed so that this method executes as
	* quickly as possible.
	*/
	LogLevel getChainedLogLevel() const;

	/**
	* Returns the assigned LogLevel, if any, for this Logger.  
	*           
	* @return LogLevel - the assigned LogLevel, can be <code>NOT_SET_LOG_LEVEL</code>.
	*/
	LogLevel getLogLevel() const;

	/**
	* Set the LogLevel of this Logger.
	*/
	void setLogLevel(LogLevel ll);

	/**
	* Return the the {@link Hierarchy} where this <code>Logger</code> instance is
	* attached.
	*/
	Hierarchy& getHierarchy() const;

	/**
	* Return the logger name.  
	*/
	std::string const& getName() const;

	// AppenderAttachable Methods
	virtual void addAppender(SharedAppenderPtr newAppender);

	virtual SharedAppenderPtrList getAllAppenders();

	virtual SharedAppenderPtr getAppender(const std::string& name);

	virtual void removeAllAppenders();

	virtual void removeAppender(SharedAppenderPtr appender);

	virtual void removeAppender(const std::string& name);

	Logger ();
	Logger(const Logger& rhs);
	Logger& operator= (const Logger& rhs);
	virtual ~Logger();

	void swap (Logger &);

	/**
	* Used to retrieve the parent of this Logger in the
	* Logger tree.
	*/
	Logger getParent() const;

protected:
		
	/** This is a pointer to the implementation class. */
	LoggerImpl * _pLoggerImpl;

private:
		
	/**
	* This constructor created a new <code>Logger</code> instance 
	* with a pointer to a Logger implementation.
	* 
	* You should not create loggers directly.
	*
	* @param ptr A pointer to the Logger implementation.  This value cannot be NULL.  
	*/
	Logger(LoggerImpl * ptr);

	// Friends
	friend class log4cplus::LoggerImpl;
	friend class log4cplus::Hierarchy;
	friend class log4cplus::HierarchyLocker;
	friend class log4cplus::DefaultLoggerFactory;
};


/**
* This class is used to create the default implementation of the Logger class
*/
class LOG4CPLUS_EXPORT DefaultLoggerFactory : public LoggerFactory 
{
public:
	Logger makeNewLoggerInstance(const std::string& name, Hierarchy& h);
};


} // namespace log4cplus


#endif // LOG4CPLUS_LOGGERHEADER_
