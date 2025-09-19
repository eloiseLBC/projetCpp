#include "resource.hpp"


inline std::string generateUniqueId()
{
    // 1️⃣ compteur global (thread‑safe)
    static std::atomic<std::uint64_t> counter{0};

    // 2️⃣ horodatage haute résolution (nanosecondes depuis epoch)
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    const std::uint64_t ts = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();

    // 3️⃣ identifiant du thread (facultatif, aide à la déduplication)
    const auto tid = std::this_thread::get_id();
    std::ostringstream tidStream;
    tidStream << tid;                     // convertit le std::thread::id en texte

    // 4️⃣ compose le résultat
    std::ostringstream out;
    out << ts << '-'
        << std::setw(6) << std::setfill('0') << counter.fetch_add(1, std::memory_order_relaxed) << '-'
        << tidStream.str();

    return out.str();
}


inline int hashId(const std::string& uid)
{
    // std::hash retourne size_t ; on le tronque en int
    return static_cast<int>(std::hash<std::string>{}(uid));
}

// ----- Resource -------------------------------------------------
Resource::Resource(std::string id, std::string title, std::string author)
    : id_(id), title_(std::move(title)), author_(std::move(author)) {}

bool Resource::contains(const std::string& search) const {
    return title_.find(search) != std::string::npos ||
           author_.find(search) != std::string::npos;
}

void Resource::compactedDisplay() const {
    std::cout << "[" << id_ << "] "
              << getType() << " – "
              << title_ << " (" << author_ << ')'
              << (borrowed_ ? " ⟶ emprunté" : "") << '\n';
}

void Resource::detailledDisplay() const {
    std::cout << "ID       : " << id_ << '\n'
              << "Type     : " << getType() << '\n'
              << "Titre    : " << title_ << '\n'
              << "Auteur   : " << author_ << '\n'
              << "Emprunté : " << (borrowed_ ? "Oui" : "Non") << '\n';
}

std::string Resource::toString() const {
    return id_ + "|" + getType() + "|" +
           title_ + "|" + author_ + "|" + (borrowed_ ? "1" : "0");
}

std::string  Resource::getId()      const { return id_; }
bool Resource::isBorrowed() const { return borrowed_; }
void Resource::setBorrowed(bool b) { borrowed_ = b; }

// ----- Book ----------------------------------------------------

Book::Book(std::string title,
           std::string author,
           int yearPublished,
           int numberPages,
           std::string collection,
           std::string summary)
    : Resource(                                   // <-- appel du ctor de Resource
          std::to_string(hashId(generateUniqueId())),            // id unique (int)
          std::move(title),
          std::move(author)),
      yearPublished_(yearPublished),
      numberPages_(numberPages),
      collection_(std::move(collection)),
      summary_(std::move(summary))
{}

std::string Book::getType() const { return "Book"; }

bool Book::contains(const std::string& search) const {
    if (Resource::contains(search)) return true;
    return collection_.find(search) != std::string::npos ||
           summary_.find(search)    != std::string::npos;
}

void Book::detailledDisplay() const {
    Resource::detailledDisplay();
    std::cout << "Année    : " << yearPublished_ << '\n'
              << "Pages    : " << numberPages_ << '\n'
              << "Collection: " << collection_ << '\n'
              << "Résumé   : " << summary_ << '\n';
}

std::string Book::toString() const {
    return Resource::toString() + "|" +
           std::to_string(yearPublished_) + "|" +
           std::to_string(numberPages_) + "|" +
           collection_ + "|" + summary_;
}

