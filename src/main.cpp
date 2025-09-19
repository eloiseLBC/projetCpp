#include <iostream>

#include "models/Book.h"
#include "models/VHS.h"
#include "models/Article.h"
#include "models/DigitalResource.h"

using namespace std;

int main() {
    // Book b1("1984", "George Orwell", false, 1949, 328, "Dystopian", "A dystopian social science fiction novel and cautionary tale about the dangers of totalitarianism.");
    // b1.detailedDisplay();
    // b1.compactedDisplay();
    // cout << "Type: " << b1.getType() << endl;
    // cout << "String Representation: " << b1.toString() << endl;

    // VHS v1("Inception", "Christopher Nolan", true, 8880, "Warner Bros.");
    // v1.detailedDisplay();
    // v1.compactedDisplay();
    // cout << "Type: " << v1.getType() << endl;

    // CD c1("Thriller", "Michael Jackson", false, 2580, 9, "Epic Records");
    // c1.detailedDisplay();
    // c1.compactedDisplay();
    // cout << "Type: " << c1.getType() << endl;

    // DVD d1("The Dark Side of the Moon", "Pink Floyd", true, 2580, 10, "Harvest Records");
    // d1.detailedDisplay();
    // d1.compactedDisplay();
    // cout << "Type: " << d1.getType() << endl;

    DigitalResource dr1("E-book on C++", "Bjarne Stroustrup", false, "PDF", 2048000, "/ebooks/cpp.pdf");
    dr1.detailedDisplay();
    dr1.compactedDisplay();
    cout << "String Representation: " << dr1.toString() << endl;

    Article a1("Science Today", "Various Authors", true, 2023, 120, "Science", "A monthly science magazine.", "SciMag Publishers", 5, "The Future of AI");
    a1.detailedDisplay();
    a1.compactedDisplay();
    cout << "Name: " << a1.getName() << endl;
    cout << "Type: " << a1.getType() << endl;
    cout << "String Representation: " << a1.toString() << endl;

    return 0;
}
