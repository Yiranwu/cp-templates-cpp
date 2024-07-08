//
// Created by Andrew Wu on 7/7/24.
//

#ifndef STRUCTUREDBINDINGNOTE_H
#define STRUCTUREDBINDINGNOTE_H

// Structured binding to unpack values:
auto [u, v] = make_tuple(3,4);

// Assigning existing variable
std::tie(u,v) = make_tuple(3,4);

#endif //STRUCTUREDBINDINGNOTE_H
