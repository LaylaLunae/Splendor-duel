#ifndef JETON_H
#define JETON_H

#include <string>

class Jeton {
protected:
    std::string chemin_vers_image;
public:
    Jeton() {}
    virtual ~Jeton() {}

    virtual void afficher() const = 0;
};

#endif // JETON_H
