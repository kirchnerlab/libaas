/*
 * Error.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2009,2011,2012 Marc Kirchner
 * Copyright (c) 2009 Bernhard Kausler
 *
 */

#ifndef __LIBAAS_INCLUDE_AAS_ERROR_HPP__
#define __LIBAAS_INCLUDE_AAS_ERROR_HPP__

#include <aas/Types.hpp>

#include <exception>
#include <string>
#include <cassert>

namespace aas {
namespace errors {

/**Base class for all aas exceptions.
 */
class Exception : public std::exception
{
public:
    /**Default constructor.
     * @param[in] message The reason/description of the exception
     */
    Exception(const aas::Char* message)
    {
        what_ = message;
    }

    /**Default constructor.
     * @param[in] message The reason/description of the exception
     */
    Exception(const aas::String& message)
    {
        what_ = message;
    }

    /**Descructor.
     */
    virtual ~Exception() throw ()
    {
    }

    /**Returns the reason/description of the exception
     * @returns Reason/description of the exception.
     */
    virtual const char* what() const throw ()
    {
        return what_.c_str();
    }

protected:

    /** Exception message.
     */
    aas::String what_;

};
// class Exception

/**A LogicError is used for invalid external input or code bugs.
 */
class LogicError : public aas::errors::Exception
{
public:
    /**Default constructor.
     * @param[in] message The reason/description of the exception
     */
    explicit LogicError(const char* message) :
            Exception(message)
    {
    }

    /**Default constructor.
     * @param[in] message The reason/description of the exception
     */
    explicit LogicError(const aas::String& message) :
            Exception(message)
    {
    }

    /**Desctructor.
     */
    virtual ~LogicError() throw ()
    {
    }

};
// class LogicError

/**Runtime errors are caused by not acquirable system resources or unexpected failures.
 */
class RuntimeError : public aas::errors::Exception
{
public:
    /**Default constructor.
     * @param[in] message The reason/description of the exception
     */
    explicit RuntimeError(const char* message) :
            Exception(message)
    {
    }

    /**Default constructor.
     * @param[in] message The reason/description of the exception
     */
    explicit RuntimeError(const aas::String& message) :
            Exception(message)
    {
    }

    /**Destructor.
     */
    virtual ~RuntimeError() throw ()
    {
    }

};
// class RuntimeError

/**Out of range exceptions.
 */
class OutOfRange : public LogicError
{
public:
    /**Default constructor.
     * @param[in] message The reason/description of the exception
     */
    explicit OutOfRange(const char* message) :
            LogicError(message)
    {
    }

    /**Default constructor.
     * @param[in] message The reason/description of the exception
     */
    explicit OutOfRange(const aas::String& message) :
            LogicError(message)
    {
    }

    /**Destructor.
     */
    virtual ~OutOfRange() throw ()
    {
    }

};
// class OutOfRange

/**Throws a LogicError in case the predicate is not true.
 * @param[in] predicate Predicate
 * @param[in] message Message
 * @throws Throws a LogicError in case the predicate is not true
 */
inline void throw_logic_error(aas::Bool predicate, const char* message)
{
    if (!predicate) {
        throw aas::errors::LogicError(message);
    }
}

/**Throws an OutOfRange exceptions in case the predicate is not true.
 * @param[in] predicate
 * @param[in] message
 * @throws Throws an OutOfRange exception in case the predicate is not true.
 */
inline void throw_outofrange_error(aas::Bool predicate, const char* message)
{
    if (!predicate) {
        throw aas::errors::OutOfRange(message);
    }
}

/**Convenience definition to easily throw a LogicError.
 */
#define aas_logic_error_cond(PREDICATE, MESSAGE) aas::errors::throw_logic_error(PREDICATE, MESSAGE)
/**Convenience definition to easily throw a LogicError.
 */
#define aas_logic_error(MESSAGE) throw aas::errors::LogicError(MESSAGE)

/**Convenience definition to easily throw an OutOfRange.
 */
#define aas_outofrange_cond(PREDICATE, MESSAGE) aas::errors::throw_outofrange_error(PREDICATE, MESSAGE)
/**Convenience definition to easily throw an OutOfRange.
 */
#define aas_outofrange(MESSAGE) throw aas::errors::OutOfRange(MESSAGE)

/**Convenience definition to easily throw a RunTimeError.
 */
#define aas_fail(MESSAGE) throw aas::errors::RuntimeError (MESSAGE)

} // namespace errors
} // namespace aas

#endif /* __LIBAAS_INCLUDE_AAS_ERROR_HPP__ */
