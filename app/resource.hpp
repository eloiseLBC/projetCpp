#pragma once
#include <string>
#include <iostream>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <thread>   // std::this_thread::get_id()
#include <functional>

// ---------- classe abstraite ----------
class Resource {
protected:
    std::string         id_;
    std::string title_;
    std::string author_;
    bool        borrowed_ = false;

public:
    Resource() = default;
    Resource(std::string id, std::string title, std::string author);
    virtual ~Resource() = default;

    // Interface publique (déclarations uniquement)
    virtual bool contains(const std::string& search) const;
    virtual void compactedDisplay() const;
    virtual void detailledDisplay() const;
    virtual std::string getType() const = 0;
    virtual std::string toString() const;

    // Accesseurs simples
    std::string  getId()      const;
    bool isBorrowed() const;
    void setBorrowed(bool);
};

// ---------- classe concrète ----------
class Book : public Resource {
private:
    int         yearPublished_;
    int         numberPages_;
    std::string collection_;
    std::string summary_;

public:
    Book(
         std::string title,
         std::string author,
         int yearPublished,
         int numberPages,
         std::string collection,
         std::string summary);

    // Redéfinitions
    std::string getType() const override;
    bool        contains(const std::string& search) const override;
    void        detailledDisplay() const override;
    std::string toString() const override;
};