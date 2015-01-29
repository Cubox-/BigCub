//
//  vmanip.t.h++
//  bigcub
//
//  Created by Andy Pilate on 29/01/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#ifndef vmanip_t_h
#define vmanip_t_h

#include "vmanip.h++"

template<typename T, typename>
vmanip::Type vmanip::intImport(T const &n) {
    Type toReturn;
    toReturn.reserve(sizeof(n) * CHAR_BIT);
    
    for (size_type i = 0; i < sizeof(n) * CHAR_BIT; ++i) {
        toReturn.push_back((n >> i) & 1);
    }
    
    if (std::is_unsigned<T>::value) { // If unsigned, we need to convert into
        toReturn.push_back(false);    // signed form.
    }
    
    compress(toReturn);
    return toReturn;
}

template<typename T, typename>
T vmanip::intExport(Type const &n) {
    T toReturn = 0;
    
    if (n.size() == 0) {
        return toReturn;
    }
    
    size_type i = 0;
    for (; (i < n.size()) && i < sizeof(T) * CHAR_BIT; ++i) {
        toReturn |= (static_cast<T>(n[i]) << i);
    }
    
    for (; n.back() == true && i < sizeof(T) * CHAR_BIT; ++i) {
        toReturn |= (static_cast<T>(n.back()) << i);
    }
    
    return toReturn;
}

template<class BinaryOperation>
void vmanip::transform(Type a, Type b, Type &dest, BinaryOperation op) {
    extend(a, b);
    
    dest.resize(a.size());
    
    for (auto i : dest) {
        dest[i] = op(a[i], b[i]);
    }
    
    compress(dest);
}

template<class UnaryOperation>
void vmanip::transform(Type &dest, UnaryOperation op) {
    for (auto i : dest) {
        dest[i] = op();
    }
}

#endif