#include <iostream>
#include <cmath> 
#include <iomanip>

//1. LES FONCTIONS OUTILS 

// Fonction Loi Normale Cumulative N(x)
double N(double x) {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

// Fonction pour calculer d1
double calcul_d1(double spot, double strike, double r, double vol, double time) { 
    return (std::log(spot / strike) + (r + (std::pow(vol, 2) / 2.0)) * time) / (vol * std::sqrt(time));
}

// Fonction pour calculer d2
double calcul_d2(double d1, double vol, double time) {
    return d1 - vol * std::sqrt(time);
}

// 2. Main ==> on utilise les fonctions outils 

int main() {
    // Variables de marché (DAta)
    double spot = 100.0;
    double strike = 100.0;
    double r = 0.05;
    double vol = 0.2;
    double time = 1.0;

    // 2.1 : Calcul des variables intermédiaires
    double d1 = calcul_d1(spot, strike, r, vol, time);
    double d2 = calcul_d2(d1, vol, time);

    // 2.2 : Calcul des prix (Call et Put)
    double Call = spot * N(d1) - strike * std::exp(-r * time) * N(d2);
    double Put = strike * std::exp(-r * time) * N(-d2) - spot * N(-d1);

    // 2.3 : Affichage des résultats
    std::cout << std::fixed << std::setprecision(4); // 4 décimales pour la précision (coutume)
    std::cout << "========= PRICER BLACK-SCHOLES =========" << "\n";
    std::cout << "Prix du Call : " << Call << " EUR" << "\n";
    std::cout << "Prix du Put  : " << Put << " EUR" << "\n";
    std::cout << "----------------------------------------" << "\n";
    std::cout << "Delta (Hedging) : " << N(d1) << "\n";
    std::cout << "Strategie : Achetez " << N(d1) << " actions pour couvrir 1 Call." << "\n";
    std::cout << "========================================" << "\n";

    return 0;
}