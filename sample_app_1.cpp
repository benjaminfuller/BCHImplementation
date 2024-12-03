/**********************************************************************
   Project: C++ Library for General Galois Field Arithmetic

   Language: C++ 2007	   
   Author: Saied H. Khayat
   Date:   Feb 2013
   URL: https://github.com/saiedhk
   
   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

**********************************************************************/

// A simple example showing how to use the GaloisCPP library.

#include <iostream>
#include "gfelement.h"

using namespace std;
using namespace shk_galoiscpp;

// Let's say you need to work with GF(17^6).

// You need to fix two parameters: modulus and dimension.
// You may define them as constants, e.g.:
const Fint MODULUS = 2;   // modulus of the prime field
const Int DIM = 984;         // dimesion of extension field
const Int number_nonzero = 5;

// You also need to have a reduction polynomial, which is an irreducible
// polynomial of degree equal to DIM over the prime field GF(MODULUS).
// For example, we know f(x) = x^6 + x^5 + x^4 + x^3 + x^2 + x + 1
// is one such polynomial for MODULUD=17 and DIM=6.
//
// The above polynomial will serve as the reduction polynomial for GF(17^6).
// You should define an array containing the coefficients of that polynomial.
Fint nonzero_poly_coefficients[5] = {0,3, 9, 24, 984};
Fint reduction_polynomial_coefficients[DIM+1];


// NOTE: There are two compulsory conditions that you have to take care and
// the library will not check their validity.
// (1) choice of a prime number for MODULUS,
// (2) choice of an irreducible polynomial over the prime field GF(MODULUS).


// Let's also define three array containing the coefficients of three Galois Field
// elements (i.e. polynomials over the prime field GF(MODULUS) ).
Fint Apoly[DIM] = {1,5,11,4,13,2};
Fint Bpoly[DIM] = {12,15,1,3,14,12};
Fint Cpoly[DIM] = {9,3,13,14,7,5};
// Remember: In the above arrays, the polynomial coefficients are written in
// the order of increasing degree. For example,
// Apoly = 1 + 5 x + 11 x^2 + 4 x^3 + 13 x^4 + 2 x^5

void convert_non_zero_to_irreducible(Fint (&reduction_polynomial_coeff)[DIM+1], Fint nonzero_poly[number_nonzero]){
   Fint current_pos_nonzero_array = 0;
   for(int i=0; i<DIM+1; i++){
      if(i==nonzero_poly[current_pos_nonzero_array]){
         reduction_polynomial_coeff[i] = 1;
         current_pos_nonzero_array ++;
      }
      else{
         reduction_polynomial_coefficients[i] = 0;
      }
      if(current_pos_nonzero_array == number_nonzero){
         return;
      }
   }
}

void BruteForceGenerator(GaloisField & gf){
   Fint g_cand_coeff[DIM]= { 0 };
   // GFelement g_cand(&gf, g_cand_coeff);
   GFelement g_cand(&gf);
   g_cand.setOne();
   
   GFelement g_one(g_cand);
   g_cand =g_cand+g_one;
   for(int i=0;i<5;i++){
      cout<<GFexp(g_cand, i)<<endl;
   }
   cout<< gf.getDimension()<<endl;
   // return nullg_cand;
}

int main()
{
   convert_non_zero_to_irreducible(reduction_polynomial_coefficients, nonzero_poly_coefficients);
   // cout<<reduction_polynomial_coefficients<<endl;
   // Declare and create your Galois Field.
   GaloisField myGaloisField(MODULUS, DIM, reduction_polynomial_coefficients);

   // You can print the information contained in your Galois Field.
   cout << "myGaloisField: " <<myGaloisField;
   // GFelement g = BruteForceGenerator(myGaloisField);
   BruteForceGenerator(myGaloisField);

   // // you can now declare Galois Field elements (GFelements) as follows:
   // GFelement A( &myGaloisField, Apoly );  // Initialized to Apoly
   // GFelement B( &myGaloisField, Bpoly );  // Initialized to Bpoly
   // GFelement C( &myGaloisField, Cpoly );  // Initialized to Cpoly
   // GFelement D( &myGaloisField );         // Not Initialized

   // // Now you have four GFelements A,B,C,D that you can work with.
   // // For example:
   // D = A + B * C;
   // cout << "D = A + B * C = " << D;

   // D = (A + B) / C;
   // cout << "D = (A + B) / C = " << D;

   // D = A * B * C + D;
   // cout << "D = A * B * C + D = " << D;

   // D = A - B * (-C) + B;
   // cout << "D = A - B * (-C) + B = " << D;

   // D = (3*A - 5*B + 7*C) / D;
   // cout << "D = (3*A - 5*B + 7*C) / D = " << D;

   // D = GFexp(A,100) + GFexp(B,100);  // D = A^100 + B^100
   // cout << "D = A^100 + B^100 = " << D;

   // and so on

   // Remember: In the above, the polynomial coefficients are printed in
   // the order of increasing degree starting from degree zero.

   return 0;
}
