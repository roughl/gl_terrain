//Config.hpp
#ifndef __CONFIG_HPP
#define __CONFIG_HPP
#include <SDL/SDL.h>

class Option {
enum EType {
	NUMBER,
	BOOLEAN,
	STRING
	};
public:
    Option( );
//    ~Option();
    double getNumber();
    double getNumber(bool *ok);
    bool getBoolean();
    bool getBoolean(bool *ok);
    const char *getString();
    const char *getString(bool *ok);
    int setValue(double number);
    int setValue(bool boolean);
    int setValue(const char *string);
    int overwriteValue();
    
private:
    bool set;
    EType type;
    union {
        double number;
        bool boolean;
        const char *string;
    }value;
};

#endif // __CONFIG_HPP
