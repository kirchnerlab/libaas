/*
 * Error.hpp
 *
 * Copyright (c) 2011,2012 Mathias Wilhelm
 * Copyright (c) 2009,2011,2012 Marc Kirchner
 * Copyright (c) 2009 Bernhard Kausler
 *
 */

#ifndef __LIBAAS_INCLUDE_LIBAAS_ERROR_HPP__
#define __LIBAAS_INCLUDE_LIBAAS_ERROR_HPP__

#include <libaas/Types.hpp>

#include <exception>
#include <string>
#include <cassert>

namespace libaas {
namespace errors {

class Exception : public std::exception
{
public:
    Exception(const libaas::Char* message)
    {
        what_ = message;
    }

    Exception(const libaas::String& message)
    {
        what_ = message;
    }

    virtual ~Exception() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return what_.c_str();
    }

protected:

    /** Exception message.
     */
    libaas::String what_;

};
// class Exception

/**
 * invalid external input or code bugs
 */
class LogicError : public libaas::errors::Exception
{
public:
    explicit LogicError(const char* message) :
            Exception(message)
    {
    }

    explicit LogicError(const libaas::String& message) :
            Exception(message)
    {
    }

    virtual ~LogicError() throw ()
    {
    }

};
// class LogicError

/**
 * Runtime errors caused by not acquirable system resources
 */
class RuntimeError : public libaas::errors::Exception
{
public:
    explicit RuntimeError(const char* message) :
            Exception(message)
    {
    }

    explicit RuntimeError(const libaas::String& message) :
            Exception(message)
    {
    }

    virtual ~RuntimeError() throw ()
    {
    }

};
// class RuntimeError

class OutOfRange : public LogicError
{
public:
    explicit OutOfRange(const char* message) :
            LogicError(message)
    {
    }

    explicit OutOfRange(const libaas::String& message) :
            LogicError(message)
    {
    }

    virtual ~OutOfRange() throw ()
    {
    }

};
// class OutOfRange

inline void throw_logic_error(libaas::Bool predicate, const char* message)
{
    if (!predicate) {
        throw libaas::errors::LogicError(message);
    }
}

inline void throw_outofrange_error(libaas::Bool predicate, const char* message)
{
    if (!predicate) {
        throw libaas::errors::OutOfRange(message);
    }
}

#define libaas_logic_error_cond(PREDICATE, MESSAGE) libaas::errors::throw_logic_error(PREDICATE, MESSAGE)
#define libaas_logic_error(MESSAGE) throw libaas::errors::LogicError(MESSAGE)

#define libaas_outofrange_cond(PREDICATE, MESSAGE) libaas::errors::throw_outofrange_error(PREDICATE, MESSAGE)
#define libaas_outofrange(MESSAGE) throw libaas::errors::OutOfRange(MESSAGE)

#define libaas_fail(MESSAGE) throw libaas::errors::RuntimeError (MESSAGE)

} // namespace errors
} // namespace libaas

#endif /* __LIBAAS_INCLUDE_LIBAAS_ERROR_HPP__ */
