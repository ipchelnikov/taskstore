#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

# https://codeforces.com/gym/102558/problem/A

struct Ingredient {
  std::string name;
  int vol = 0;
};

struct Energy {
  double pr = 0, f = 0, ch = 0, fv = 0;
};

struct Disch {
  std::string name;
  int num_of_friends = 0;
  std::vector<Ingredient> ingredients;

  Energy e;
};

struct Product {
  int price = 0;
  int vol = 0;
  double to_buy = 0;
};

int vol_to_uni(int v, const std::string& t) {
  if (t.compare("l") == 0 || t.compare("kg") == 0)
    v *= 1000;
  else if (t.compare("tens") == 0)
    v *= 10;

  return v;
}

int main() {
  ////////////////////////////////////////////////////////
  // Input
  ////////////////////////////////////////////////////////

  // Menu
  int num_of_disches{0};
  std::cin >> num_of_disches;

  std::vector<Disch> menu(num_of_disches);
  for (int i = 0; i < num_of_disches; ++i) {
    Disch d;

    std::cin >> d.name;
    std::cin >> d.num_of_friends;

    int num_of_ingredients{0};
    std::cin >> num_of_ingredients;

    for (int j = 0; j < num_of_ingredients; ++j) {
      Ingredient ing;
      std::string type;

      std::cin >> ing.name;
      std::cin >> ing.vol;
      std::cin >> type;

      ing.vol = vol_to_uni(ing.vol, type);
      d.ingredients.push_back(ing);
    }

    menu[i] = d;
  }

  // Fill Product & Energy catalogs
  std::unordered_map<std::string, Product> catalog_product;
  int num_of_items{0};
  std::cin >> num_of_items;
  for (int i = 0; i < num_of_items; ++i) {
    Product p;
    std::string name;
    std::string type;

    std::cin >> name;
    std::cin >> p.price;
    std::cin >> p.vol;
    std::cin >> type;

    p.vol = vol_to_uni(p.vol, type);
    catalog_product[name] = p;
  }

  std::unordered_map<std::string, Energy> catalog_energy;
  num_of_items = 0;
  std::cin >> num_of_items;
  for (int i = 0; i < num_of_items; ++i) {
    std::string name;
    std::string type;
    double vol;

    std::cin >> name;
    std::cin >> vol;
    std::cin >> type;

    vol = vol_to_uni(vol, type);

    Energy e;
    std::cin >> e.pr;
    e.pr /= vol;
    std::cin >> e.f;
    e.f /= vol;
    std::cin >> e.ch;
    e.ch /= vol;
    std::cin >> e.fv;
    e.fv /= vol;

    catalog_energy[name] = e;
  }

  ////////////////////////////////////////////////////////
  // Calc energy
  ////////////////////////////////////////////////////////
  for (auto& disch : menu) {
    for (auto i : disch.ingredients) {
      double num_of_packs = static_cast<double>(i.vol * disch.num_of_friends) /
                            catalog_product[i.name].vol;

      catalog_product[i.name].to_buy += num_of_packs;

      // Add energy
      disch.e.pr += catalog_energy[i.name].pr * i.vol;
      disch.e.f  += catalog_energy[i.name].f  * i.vol;
      disch.e.ch += catalog_energy[i.name].ch * i.vol;
      disch.e.fv += catalog_energy[i.name].fv * i.vol;
    }
  }

  ////////////////////////////////////////////////////////
  // Output
  ////////////////////////////////////////////////////////
  int total_price{0};

  for (auto i : catalog_product) {
    int rounded_up_quantity = std::ceil(i.second.to_buy);
    total_price += rounded_up_quantity * i.second.price;
  }

  std::cout << total_price << '\n';

  for (auto i : catalog_product)
    std::cout << i.first << ' ' << std::ceil(i.second.to_buy) << '\n';

  for (auto i : menu)
    std::cout << i.name << ' ' <<
                 i.e.pr << ' ' <<
                 i.e.f  << ' ' <<
                 i.e.ch << ' ' <<
                 i.e.fv << '\n';
}
