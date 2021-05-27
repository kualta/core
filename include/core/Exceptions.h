#ifndef CORE_EXCEPTIONS_H
#define CORE_EXCEPTIONS_H

#include <stdexcept>

namespace core {

/**
 * Runtime exteption indicating unexpected import file conditions that may cause
 * errors in the future.
 */
class bad_file : public std::runtime_error {
public: explicit bad_file(const string& message = "") : std::runtime_error(message) { };
};

/**
 * Runtime exteption indicating unexpected mesh object contents
 */
class bad_mesh : public std::runtime_error {
public: explicit bad_mesh(const string& message = "") : std::runtime_error(message) { };
};


}

#endif //CORE_EXCEPTIONS_H
