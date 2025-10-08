#include <iostream>
#include<fstream>
#include <cstring>
#include <ctime>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <list>
#include <set>
#include <algorithm>
#include <numeric>
#include "Menu.h"
using namespace std;
ifstream serviceIn("streaming_services.txt");
ifstream abonamentIn("abonament.txt");
const unsigned int MAX_LENGTH = 256;



class Service{
    const int ServiceId;
    static list<Service> listOfServices;
    static int generator;
    string serviceName;
    int abonament;
public:
    Service(): ServiceId(++generator){
        this->abonament = -1;
        this->serviceName="Inactiv";
    }
    Service(const string& serviceName, int abonament): ServiceId(++generator), abonament(abonament){
        this->serviceName=serviceName;
    }
    Service(const Service& other): ServiceId(other.ServiceId), abonament(other.abonament){
        this->serviceName = other.serviceName;
    }
    ~Service()=default;
    friend istream& operator>>(istream& in, Service& service){
        cout<<"Numele serviciului selectat este:"<<'\n';
        getline(in, service.serviceName);
        cout<<"Pentru a accesa serviciul, selecteaza un abonament dintre cele disponibile:"<<'\n';
        abonamentIn.clear();
        abonamentIn.seekg(0, ios::beg);
        char ab[MAX_LENGTH];
        int index = 1;
        while(abonamentIn.getline(ab, MAX_LENGTH)){
            cout<<index<<" -> "<<ab<<'\n';
            index++;
        }
        int tempAbonament;
        bool validInput = false;
        while (!validInput) {
            cout << "Pretul abonamentului selectat este(0$,10$,50$,100$): "<<'\n';
            in >> tempAbonament;
            in.get();
                try {
                    service.setAbonament(tempAbonament);
                    validInput = true;
                } catch (const std::invalid_argument& e) {
                    cout << e.what() << " Reselecteaza pretul corect." << std::endl;
                }
        }

        return in;
    }
    friend ostream& operator<<(ostream& out, const Service &service){
        cout<<"Serviciul selectat este: ";
        out<<service.serviceName<<'\n';
        cout<<"Pretul abonamentului selectat este de: ";
        out<<service.abonament<<"$"<<'\n';
        return out;
    }
    bool operator==(const Service &service) const{
        return (this->abonament==service.abonament && this->serviceName==service.serviceName);
    }
    int operator-(const Service &service)const{
        return (this->abonament - service.abonament);
    }
    bool operator>=(Service &service)const{
        return(this->abonament>=service.abonament);
    }
    int operator--(){
        return (this->abonament - 1);
    }
    bool operator<=(Service &service)const{
        return (this->abonament<=service.abonament);
    }
    Service &operator[](int index){
        if (index<0 || index>=static_cast<int>(listOfServices.size()))
            throw out_of_range("Ai introdus un serviciu care nu este activ!");
        else{
            auto it = listOfServices.begin();
            advance(it,index);
            return *it;
        }
    }
    Service &operator=(const Service &service){
        if (this != &service){
        this->abonament = service.abonament;
        this->serviceName=service.serviceName;
        }
        return *this;
    }
    static void addServiceToList(const Service& service){
        listOfServices.push_back(service);
    }
    static bool ServiceExists(const Service& service){
        auto it = find_if(listOfServices.begin(), listOfServices.end(), [&](const Service &service1){
            return service.serviceName==service1.serviceName;
        });
        return it!=listOfServices.end();
    }
    static void SchimbaAbonamentul(const Service &service){
        for (Service& service1: listOfServices) {
            if (service>=service1){
                int dif = service - service1;
                cout<<"Pentru schimbarea abonamentului trebuie achitata, in plus, suma de: "<<dif<<"$"<<" dupa finalizarea abonamentului activ."<<'\n';
                service1.setAbonament(service1.abonament);
                }
                else if (service<=service1){
                    int dif=service1 - service;
                    cout<<"Pentru schimbarea abonamentului, se va plati cu: "<<dif<<"$ mai putin decat abonamentul activ, dupa finalizarea acestuia."<<'\n';
                    service1.setAbonament(service1.abonament);
                    }
            }
    }
    static void showAllServices(){
        if (listOfServices.empty()){
            throw underflow_error("Nu exista servicii active la momentul actual.");
        }else {
            int index = 1;
            for (const Service& service: listOfServices)
            {
                cout<<index<<" -> "<<service<<'\n';
                index++;
            }
        }
    }
    static void showServicesById(){
        if (listOfServices.empty())
            throw invalid_argument("Nu exista servicii active la momentul actual.");
        else{
        for(const Service& service:listOfServices)
            cout<<service.serviceName<<" are ID-ul "<<service.ServiceId<<'\n';
        }
    }
    static void deleteServiceById(int ServiceID){
        auto it = listOfServices.begin();
        bool found = false;
        while(it != listOfServices.end()){
            if(it->ServiceId == ServiceID){
                it = listOfServices.erase(it);
                found = true;
                cout<<"Serviciul cu ID-ul " << ServiceID << " a fost sters."<<endl;
            }else {++it;}
        }
        if (!found)
            throw out_of_range("Serviciul cu ID-ul introdus nu exista.");

    }
    void setAbonament(int newAb){
        if (newAb==10 || newAb==50 || newAb==100)
            abonament=newAb;
        else throw invalid_argument("Pretul este invalid. Introduceti un pret din lista de preturi!");
    }
    void setServiceName(string name){
        serviceName=name;
    }
    int getAbonament()const {
        return this->abonament;
    }
    string getServiceName() const{
        return this->serviceName;
    }
    int getServiceId() const{
        return this->ServiceId;
    }

};
class Account{
    static set<Account> listOfAcc;
    const int AccId;
    static int nrOfAcc;
    string accountName;
    string parola;
    time_t creationTime;
public:
    Account():AccId(++nrOfAcc){
        this->accountName="Username";
        this->parola="parola1234";
        this->creationTime = time(0);

    }
    Account(const string& accountName, const string& parola):AccId(++nrOfAcc){
        this->accountName=accountName;
        this->parola=parola;
        this->creationTime = time(0);

    }
    Account(const Account& acc):AccId(++nrOfAcc),creationTime(acc.creationTime){
        this->accountName = acc.accountName;
        this->parola = acc.parola;

    }
    ~Account()=default;
    friend istream& operator>>(istream& in, Account &account){
    cout<<"Numele contului este:"<<'\n';
    in>>ws;
    getline(in,account.accountName);
    cout<<"Introdu parola:"<<'\n';
    getline(in,account.parola);
    return in;
    }
    friend ostream& operator<<(ostream& out, const Account &acc){
    out<<"Numele contului activ este: "<<acc.accountName<<'\n';
    out<<"ID-ul contului activ este: "<<acc.AccId<<'\n';
    out<<"Data la care contul a fost creat este: "<<ctime(&acc.creationTime)<<'\n';
    return out;
    }
    bool operator==(const Account &acc) const{
        return (acc.accountName==this->accountName && acc.parola==this->parola);
    }
    bool operator>=(Account &acc)const{//In sensul de comparatie al datei de creare al unui cont
        return(this->creationTime>=acc.creationTime);
    }
    bool operator<=(Account &acc)const{
        return (this->creationTime<=acc.creationTime);
    }
    Account &operator=(const Account &acc){
        if (this != &acc){
        this->accountName=acc.accountName;
        this->parola=acc.parola;
        creationTime=acc.creationTime;
        }
        return *this;
    }
     bool operator<(const Account& other) const {
            return (this->creationTime<other.creationTime);

    }
    Account &operator[](int index){
        if (index<0 || index>=static_cast<int>(listOfAcc.size()))
            throw out_of_range("Ai introdus un cont care nu exista!");
        else{
            auto it = listOfAcc.begin();
            advance(it,index);
            return const_cast<Account&>(*it);
        }
    }
    static void showAllAcc(){
        for(auto const& acc : listOfAcc)
            cout<<acc<<'\n';
    }
    static void addAccToList(const Account &acc){
        listOfAcc.insert(acc);
    }
    static bool AccountExists(const Account &acc){
       auto it = find_if(listOfAcc.begin(),listOfAcc.end(),[&](auto const& a){
            return a.accountName==acc.accountName && a.parola==acc.parola;
        }
    );
    return it != listOfAcc.end();
    }
    static bool parolaCorecta(const string& parola){
        if (parola.empty())
            throw invalid_argument("Parola nu poate fi vida!");
        auto it = find_if(listOfAcc.begin(), listOfAcc.end(), [&](auto const& a){
            return a.parola == parola;
            });
        return it!=listOfAcc.end();
    }
    static void showAllAccById(){
        for(auto const& acc:listOfAcc){
            cout<<acc.accountName<<" are ID-ul "<<acc.AccId<<endl;
        }
    }
    static void deleteAcc(int accId){
        auto it = find_if(listOfAcc.begin(), listOfAcc.end(),[&](auto const& a){
            return a.AccId == accId; }
        );
        if (it != listOfAcc.end())
            listOfAcc.erase(it);
        else
            throw out_of_range("ID-ul selectat este unul invalid. Incearca din nou!");

    }
    int getAccId()const {
        return this->AccId;
    }
    string getAccName()const{
        return this->accountName;
    }
    string getAccPass()const{
        return this->parola;
    }
    time_t getAccDate() const{
        return this->creationTime;
    }

};
class Previewable {
public:
    virtual void playPreview() const = 0;
    virtual ~Previewable() {}
};

class Film;
class Serial;
class Documentar;
class Miniseries;
class Program {
protected:
    const int ProgrId;
    static int generator;
    char *title;
    char *type;
    char *genre;
    float rating;
    static vector<Program> programsList;
    static vector<Film> filmsList;
    static vector<Serial> serialsList;
    static vector<Documentar> documentarsList;
    static vector<Miniseries> miniseriesList;

public:
    Program() : ProgrId(++generator), title(nullptr), type(nullptr), genre(nullptr), rating(0.0) {
    }

    Program(char *title, char *type, char *genre, float rate) : ProgrId(++generator), rating(rate) {
        this->title = new char[strlen(title)+1];
        strcpy(this->title, title);
        this->genre = new char[strlen(genre)+1];
        strcpy(this->genre, genre);
        this->type = new char[strlen(type)+1];
        strcpy(this->type, type);
    }

    Program(const Program &progr) : ProgrId(++generator), rating(progr.rating) {
        this->title = new char[strlen(progr.title)+1];
        strcpy(this->title, progr.title);
        this->genre = new char[strlen(progr.genre)+1];
        strcpy(this->genre, progr.genre);
        this->type = new char[strlen(progr.type)+1];
        strcpy(this->type, progr.type);
    }

    virtual ~Program() {
        delete[] title;
        delete[] type;
        delete[] genre;
    }

    friend istream& operator>>(istream &in, Program &program) {
        char dummy[MAX_LENGTH];
        cout << "Introdu numele filmului/serialului/documentarului/miniseriei pe care vrei sa-o adaugi:" << '\n';
        in.getline(dummy, MAX_LENGTH);
        program.setTitle(dummy);
        cout << "Introdu tipul acestuia (Serial/Film/Documentar/Miniseries):" << '\n';
        in.getline(dummy, MAX_LENGTH);
        program.setType(dummy);
        cout << "Introdu genul acestuia:" << '\n';
        in.getline(dummy, MAX_LENGTH);
        program.setGenre(dummy);
        cout << "Introdu rating-ul acestuia (0.0-10.0):" << '\n';
        in >> program.rating;
        in.get();
        return in;
    }

    friend ostream& operator<<(ostream &out, const Program &program) {
        out << "Numele " << program.type << "ului este: " << program.title << '\n';
        out << "Tipul programului este: " << program.type << '\n';
        out << "Genul programului este: " << program.genre << '\n';
        out << "Rating-ul programului este: " << program.rating << '\n';
        return out;
    }

    Program& operator=(const Program &p) {
        if (this != &p) {
            if (this->title != nullptr) {
                delete[] title;
            }
            if (this->genre != nullptr) {
                delete[] genre;
            }
            if (this->type != nullptr) {
                delete[] type;
            }

            this->title = new char[strlen(p.title)+1];
            this->genre = new char[strlen(p.genre)+1];
            this->type = new char[strlen(p.type)+1];
            strcpy(this->title, p.title);
            strcpy(this->genre, p.genre);
            strcpy(this->type, p.type);
            this->rating = p.rating;
        }
        return *this;
    }

    bool operator==(const Program &p) const {
        return (!strcmp(this->title, p.title) && !strcmp(this->genre, p.genre) && !strcmp(this->type, p.type) && this->rating == p.rating);
    }

    bool operator>=(const Program &p) const {
        return(this->rating >= p.rating);
    }

    bool operator<=(const Program &p) const {
        return (this->rating <= p.rating);
    }

    friend Program operator+(Program& p, float x) {
        if (p.rating+x <= 10.0)
            p.rating += x;
        return p;
    }

    Program operator+(float x) {
        if (rating+x <= 10.0)
            this->rating += x;
        return *this;
    }

    friend Program operator+(float x, Program& p) {
        if (p.rating+x <= 10.0)
            p.rating += x;
        return p;
    }

    Program& operator+=(float x) {
        if (rating+x <= 10.0)
            this->rating += x;
        return *this;
    }

    Program& operator-=(float x) {
        rating -= x;
        if(rating < 0.0)
            rating = 0.0;
        return *this;
    }

    Program operator-(Program &p) {
        this->rating = this->rating - p.rating;
        if (this->rating >= 0.0)
            return *this;
        else {
            this->rating = 0.0;
            return *this;
        }
    }

    const int getProgramId() const {
        return this->ProgrId;
    }

    char* getTitle() const {
        return this->title;
    }

    char* getGenre() const {
        return this->genre;
    }

    char* getType() const {
        return this->type;
    }

    float getRating() const {
        return this->rating;
    }

    static int getSizeOfList() {
        return programsList.size() + filmsList.size() + serialsList.size() + documentarsList.size()+miniseriesList.size();
    }

    void setTitle(const char* newTitle) {
        if (title) delete[] title;
        title = new char[strlen(newTitle)+1];
        strcpy(title, newTitle);
    }

    void setType(const char* newType) {
        if (type) delete[] type;
        type = new char[strlen(newType)+1];
        strcpy(type, newType);
    }

    void setGenre(const char* newGenre) {
        if (genre) delete[] genre;
        genre = new char[strlen(newGenre)+1];
        strcpy(genre, newGenre);
    }

    void setRating(float newRating) {
        rating = newRating;
    }

    static void addProgram(const Program& p) {
        programsList.push_back(p);
    }

    static void addFilm(const Film& f);
    static void addSerial(const Serial& s);
    static void addDocumentar(const Documentar& d);
    static void addMiniseries(const Miniseries& m);
    static void showAllPrograms();
    static void showAllProgramsById();
    static bool ProgramExists(const char* name);
    static void afiseazaRatingMaiMare(float rate);
    static void load(const char* filename);
    static void previewAllPrograms();
    static Program* findProgramById(int id);
    static void showallMiniseries();
};


class Film : public virtual Program, public Previewable {
protected:
    float duration;
    char* director;
public:
    Film(char* title, char* genre, float rating=0.0, char* director="Anonim", float durat=0.0)
        : Program(title, "Film", genre, rating), duration(durat) {
        this->director = new char[strlen(director)+1];
        strcpy(this->director, director);
    }

    Film() : Program() {
        duration = 0.0;
        director = new char[strlen("Anonim")+1];
        strcpy(director, "Anonim");
        if(!getType()) {
            setType("Film");
        }
    }

    Film(const Film &other) : Program(other), duration(other.duration) {
        this->director = new char[strlen(other.director)+1];
        strcpy(this->director, other.director);
    }

    Film& operator=(const Film &other) {
        if (this != &other) {
            Program::operator=(other);
            duration = other.duration;

            if (director) {
                delete[] director;
            }
            director = new char[strlen(other.director)+1];
            strcpy(director, other.director);
        }
        return *this;
    }
    virtual ~Film() {
        delete[] director;
    }

    friend istream &operator>>(istream &in, Film &f) {
        char dummy[MAX_LENGTH];
        float rating, dur;
        cout << "Numele filmului este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (f.title) delete[] f.title;
        f.title = new char[strlen(dummy) + 1];
        strcpy(f.title, dummy);
        cout << "Genul filmului este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (f.genre) delete[] f.genre;
        f.genre = new char[strlen(dummy)+1];
        strcpy(f.genre, dummy);
        if (f.type) delete[] f.type;
        f.type = new char[strlen("Film")+1];
        strcpy(f.type, "Film");
        cout << "Rating-ul filmului este de(0.0-10.0): " << endl;
        in >> rating;
        f.rating = rating;
        in.get();
        cout << "Introdu durata filmului(minute): " << endl;
        in >> dur;
        f.duration = dur;
        in.get();
        cout << "Directorul filmului este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (f.director) delete[] f.director;
        f.director = new char[strlen(dummy)+1];
        strcpy(f.director, dummy);

        return in;
    }

    friend ostream& operator<<(ostream &out, const Film &f) {
        out << static_cast<const Program&>(f);
        out << "Durata filmului este de: " << f.duration << " minute." << endl;
        out << "Directorul filmului este: " << f.director << "." << endl;
        return out;
    }

    virtual void playPreview() const override {
        cout << "Preview pentru filmul " << getTitle() << " regizat de catre " << director << "." << endl;
        cout << "Durata filmului este de " << duration << " minute." << endl;
    }

    float getDuration() const {
        return duration;
    }

    char* getDirector() const {
        return director;
    }
};

class Serial : public virtual Program, public virtual Previewable {
protected:
    int seasons, nrEpisodes;
public:
    Serial(char* title, char* genre, float rating=0.0, int nrSeason=0, int nrEp=0): Program(title, "Serial", genre, rating), seasons(nrSeason), nrEpisodes(nrEp) {}
    Serial() : Program() {
        seasons = 0;
        nrEpisodes = 0;
        if (!getType())
            setType("Serial");
    }
    Serial(const Serial &other) : Program(other), seasons(other.seasons), nrEpisodes(other.nrEpisodes) {}
    virtual ~Serial() {}
    Serial& operator=(const Serial &s) {
        if (this != &s) {
            Program::operator=(s);
            this->nrEpisodes = s.nrEpisodes;
            this->seasons = s.seasons;
        }
        return *this;
    }

    virtual void playPreview() const override {
        cout << "Preview pentru serialul " << getTitle() << "." << endl;
        cout << "Numarul de sezoane este de " << seasons << ", iar numarul de episoade este de " << nrEpisodes << "." << endl;
    }

    friend istream &operator>>(istream &in, Serial &s) {
        float rating;
        int nrs, nre;
        char dummy[MAX_LENGTH];
        cout<<"Numele serialului este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (s.title)
            delete[] s.title;
        s.title = new char[strlen(dummy) + 1];
        strcpy(s.title, dummy);
        cout<<"Genul serialului este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (s.genre)
            delete[] s.genre;
        s.genre = new char[strlen(dummy)+1];
        strcpy(s.genre, dummy);
        if (s.type)
            delete[] s.type;
        s.type = new char[strlen("Serial")+1];
        strcpy(s.type, "Serial");
        cout<<"Rating-ul serialului este de(0.0-10.0): " << endl;
        in>>rating;
        s.rating = rating;
        in.get();
        cout<<"Numarul de sezoane este de:" << endl;
        in>>nrs;
        s.seasons = nrs;
        in.get();
        cout<<"Numarul total de episoade este de:" << endl;
        in>>nre;
        s.nrEpisodes = nre;
        in.get();

        return in;
    }

    friend ostream &operator<<(ostream &out, const Serial &s) {
        out<<static_cast<const Program&>(s) << endl;
        out<<"Numarul de sezoane este de: " << s.seasons << ", iar de episoade este de: " << s.nrEpisodes << "." << endl;
        return out;
    }

    int getSeasons() const {
        return seasons;
    }

    int getEpisodes() const {
        return nrEpisodes;
    }
};

class Documentar : public Serial, public Film {
protected:
    int nrEpisod;
    float durata;
public:
    Documentar(char* title, char* genre, float rating, int nrEpisod, float durata)
        : Program(title, "Documentar", genre, rating),
          Film(),
          Serial(),
          nrEpisod(nrEpisod), durata(durata) { }

    Documentar() : Program(), Film(), Serial(), nrEpisod(0), durata(0.0f) {
        if (type) { delete[] type; }
        type = new char[strlen("Documentar") + 1];
        strcpy(type, "Documentar");
    }

    Documentar(const Documentar &other)
        : Program(other), Film(other), Serial(other), nrEpisod(other.nrEpisod), durata(other.durata) {}

    Documentar& operator=(const Documentar &other) {
        if (this != &other) {
            Program::operator=(other);
            if (director) {
                delete[] director;
            }
            director = new char[strlen(other.director)+1];
            strcpy(director, other.director);
            duration = other.duration;
            seasons = other.seasons;
            nrEpisodes = other.nrEpisodes;
            nrEpisod = other.nrEpisod;
            durata = other.durata;
        }
        return *this;
    }
    virtual ~Documentar() { }
    virtual void playPreview() const override {
        cout << "Preview pentru documentarul: " << getTitle() << endl;
        if (nrEpisod > 1) {
            cout << "Acest documentar este impartit in: " << nrEpisod << " episoade. ";
            cout << "Acesta are o durata de  " << durata << " minute." << endl;
        } else {
            cout << "Acesta este un documentar autonom cu durata de: " << durata << " minute." << endl;
        }
    }

    friend istream &operator>>(istream &in, Documentar &d) {
        float rating;
        int nrs, nre;
        char dummy[MAX_LENGTH];

        cout << "Numele documentarului este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (d.title) delete[] d.title;
        d.title = new char[strlen(dummy) + 1];
        strcpy(d.title, dummy);

        cout << "Genul documentarului este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (d.genre) delete[] d.genre;
        d.genre = new char[strlen(dummy)+1];
        strcpy(d.genre, dummy);

        if (d.type) delete[] d.type;
        d.type = new char[strlen("Documentar")+1];
        strcpy(d.type, "Documentar");

        cout << "Rating-ul documentarului este de(0.0-10.0): " << endl;
        in >> rating;
        d.rating = rating;
        in.get();

        cout << "Numarul de episoade este de:" << endl;
        in >> nrs;
        d.nrEpisod = nrs;
        in.get();

        cout << "Durata totala este de(minute):" << endl;
        in >> nre;
        d.durata = nre;
        in.get();

        return in;
    }

    friend ostream &operator<<(ostream &out, const Documentar &d) {
        out << static_cast<const Program&>(d) << endl;
        out << "Numarul de episoade este de: " << d.nrEpisod << ", cu o durata totala de: " << d.durata << " minute." << endl;
        return out;
    }

    int getNrEpisod() const {
        return nrEpisod;
    }

    float getDurata() const {
        return durata;
    }
};
class Miniseries : public Film {
protected:
    int nrEpisodes;
    float episodeDuration;

public:
    Miniseries(char* title, char* genre, float rating = 0.0, char* director = "Anonim",
               int episodes = 1, float epDuration = 0.0)
        : Program(title, "Miniseries", genre, rating),
        Film(title,genre,rating,director,epDuration*episodes),
          nrEpisodes(episodes), episodeDuration(epDuration) {
        if (type) delete[] type;
        type = new char[strlen("Miniseries") + 1];
        strcpy(type, "Miniseries");
    }

    Miniseries() :Program(), Film(), nrEpisodes(1), episodeDuration(0.0) {
        if (type) delete[] type;
        type = new char[strlen("Miniseries") + 1];
        strcpy(type, "Miniseries");
    }

    Miniseries(const Miniseries& other)
        : Program(other), Film(other), nrEpisodes(other.nrEpisodes), episodeDuration(other.episodeDuration) {}

    Miniseries& operator=(const Miniseries& other) {
        if (this != &other) {
            Film::operator=(other);
            nrEpisodes = other.nrEpisodes;
            episodeDuration = other.episodeDuration;
        }
        return *this;
    }

    virtual ~Miniseries() {}

    virtual void playPreview() const override {
        cout << "Preview pentru miniseria " << getTitle() << " regizata de catre " << director << "." << endl;
        cout << "Aceasta contine " << nrEpisodes << " episoade, fiecare cu durata de "
             << episodeDuration << " minute." << endl;
        cout << "Durata totala este de " << duration << " minute." << endl;
    }

    friend istream& operator>>(istream& in, Miniseries& m) {
        char dummy[MAX_LENGTH];
        float rating, epDur;
        int episodes;

        cout << "Numele miniseriei este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (m.title) delete[] m.title;
        m.title = new char[strlen(dummy) + 1];
        strcpy(m.title, dummy);

        cout << "Genul miniseriei este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (m.genre) delete[] m.genre;
        m.genre = new char[strlen(dummy) + 1];
        strcpy(m.genre, dummy);

        if (m.type) delete[] m.type;
        m.type = new char[strlen("Miniseries") + 1];
        strcpy(m.type, "Miniseries");

        cout << "Rating-ul miniseriei este de(0.0-10.0): " << endl;
        in >> rating;
        m.rating = rating;
        in.get();

        cout << "Numarul de episoade este: " << endl;
        in >> episodes;
        m.nrEpisodes = episodes;
        in.get();

        cout << "Durata unui episod(minute): " << endl;
        in >> epDur;
        m.episodeDuration = epDur;
        m.duration = episodes * epDur;
        in.get();

        cout << "Directorul miniseriei este: " << endl;
        in.getline(dummy, MAX_LENGTH);
        if (m.director) delete[] m.director;
        m.director = new char[strlen(dummy) + 1];
        strcpy(m.director, dummy);

        return in;
    }

    friend ostream& operator<<(ostream& out, const Miniseries& m) {
        out << static_cast<const Program&>(m);
        out << "Numarul de episoade: " << m.nrEpisodes << endl;
        out << "Durata per episod: " << m.episodeDuration << " minute." << endl;
        out << "Durata totala: " << m.duration << " minute." << endl;
        out << "Directorul miniseriei este: " << m.getDirector() << "." << endl;
        return out;
    }

    int getNrEpisodes() const {
        return nrEpisodes;
    }

    float getEpisodeDuration() const {
        return episodeDuration;
    }
    void setNrEpisodes(int episodes) {
        nrEpisodes = episodes;
        duration = episodes * episodeDuration;
    }

    void setEpisodeDuration(float epDuration) {
        episodeDuration = epDuration;
        duration = nrEpisodes * epDuration;
    }
};
void Program::addFilm(const Film& f) {
    filmsList.push_back(f);
}

void Program::addSerial(const Serial& s) {
    serialsList.push_back(s);
}

void Program::addDocumentar(const Documentar& d) {
    documentarsList.push_back(d);
}
void Program::addMiniseries(const Miniseries& m){
    miniseriesList.push_back(m);
}
void Program::showAllPrograms() {
    for (auto& p : programsList) {
        cout << p << "\n";
    }
    for (auto& f : filmsList) {
        cout << f << "\n";
    }
    for (auto& s : serialsList) {
        cout << s << "\n";
    }
    for (auto& d : documentarsList) {
        cout << d << "\n";
    }
    for (auto& m:miniseriesList){
        cout<<m<<"\n";
    }
}

void Program::showAllProgramsById() {
    for (auto& p : programsList) {
        cout << p.type << "ul cu numele " << p.title<< " are ID-ul " << p.ProgrId << "\n";
    }
    for (auto& f : filmsList) {
        cout << f.getType() << "ul cu numele " << f.getTitle()<< " are ID-ul " << f.getProgramId() << "\n";
    }
    for (auto& s : serialsList) {
        cout << s.getType() << "ul cu numele " << s.getTitle()<< " are ID-ul " << s.getProgramId() << "\n";
    }
    for (auto& d : documentarsList) {
        cout << d.getType() << "ul cu numele " << d.getTitle()<< " are ID-ul " << d.getProgramId() << "\n";
    }
    for (auto& m : miniseriesList) {
        cout << m.getType() << "ul cu numele " << m.getTitle()<< " are ID-ul " << m.getProgramId() << "\n";
    }
}
Program* Program::findProgramById(int id) {
    for (auto &p : programsList) {
        if (p.getProgramId() == id)
            return &p;
    }
    for (auto &f : filmsList) {
        if (f.getProgramId() == id)
            return &f;
    }
    for (auto &s : serialsList) {
        if (s.getProgramId() == id)
            return &s;
    }
    for (auto &d : documentarsList) {
        if (d.getProgramId() == id)
            return &d;
    }
    for (auto &m : miniseriesList) {
        if (m.getProgramId() == id)
            return &m;
    }
    return nullptr;
}
bool Program::ProgramExists(const char* name) {
    for (auto& p : programsList) {
        if (!strcmp(p.title, name))
            return true;
    }
    for (auto& f : filmsList) {
        if (!strcmp(f.getTitle(), name))
            return true;
    }
    for (auto& s : serialsList) {
        if (!strcmp(s.getTitle(), name))
            return true;
    }
    for (auto& d : documentarsList) {
        if (!strcmp(d.getTitle(), name))
            return true;
    }
     for (auto& m : miniseriesList) {
        if (!strcmp(m.getTitle(), name))
            return true;
    }
    return false;
}

void Program::afiseazaRatingMaiMare(float rate) {
    for (auto& p : programsList) {
        if (p.rating >= rate)
            cout << p << "\n";
    }
    for (auto& f : filmsList) {
        if (f.getRating() >= rate)
            cout << f << "\n";
    }
    for (auto& s : serialsList) {
        if (s.getRating() >= rate)
            cout << s << "\n";
    }
    for (auto& d : documentarsList) {
        if (d.getRating() >= rate)
            cout << d << "\n";
    }
     for (auto& m : miniseriesList) {
        if (m.getRating() >= rate)
            cout << m << "\n";
    }
}

void Program::load(const char* filename) {
    ifstream ProgramIn(filename);
      if (!ProgramIn) {
        throw runtime_error(string("Fisierul: ")+filename + string(" nu poate fi deschis."));
    }
    char line[MAX_LENGTH];

    while(ProgramIn.getline(line, MAX_LENGTH)) {
        char *title = strtok(line, ",");
        char *type = strtok(nullptr, ",");
        char *genre = strtok(nullptr, ",");
        char *ratingStr = strtok(nullptr, ",");
        if(title && type && genre && ratingStr) {
            float rating = atof(ratingStr);

            if (strcmp(type, "Film") == 0) {
                char *director = strtok(nullptr, ",");
                char *durataStr = strtok(nullptr,",");
                float durata = atof(durataStr);
                Film f(title, genre, rating, director, durata);
                filmsList.push_back(f);
            } else if (strcmp(type, "Serial") == 0) {
                char *seasonStr = strtok(nullptr,",");
                int season = atoi(seasonStr);
                char *episodeStr= strtok(nullptr, ",");
                int episode = atoi(episodeStr);
                Serial s(title, genre, rating, season, episode);
                serialsList.push_back(s);
            } else if (strcmp(type, "Documentar") == 0) {
                char *seasonStr = strtok(nullptr,",");
                int season = atoi(seasonStr);
                char *episodeStr= strtok(nullptr, ",");
                int episode = atoi(episodeStr);
                Documentar d(title, genre, rating, season, episode);
                documentarsList.push_back(d);
            } else if (strcmp(type, "Miniseries") == 0) {
                    char *director = strtok(nullptr, ",");
                    char *episodesStr = strtok(nullptr, ",");
                    int episodes = atoi(episodesStr);
                    char *epDurationStr = strtok(nullptr, ",");
                    float epDuration = atof(epDurationStr);
                    Miniseries m(title, genre, rating, director, episodes, epDuration);
                    miniseriesList.push_back(m);
                }else {
                Program p(title, type, genre, rating);
                programsList.push_back(p);
            }
        }
    }
}

void Program::previewAllPrograms() {
    cout << "Preview-uri pentru toate programele:\n";
    for (auto& f : filmsList) {
        f.playPreview();
        cout << "-------------------------\n";
    }

    for (auto& s : serialsList) {
        s.playPreview();
        cout << "-------------------------\n";
    }

    for (auto& d : documentarsList) {
        d.playPreview();
        cout << "-------------------------\n";
    }
    for (auto& m : miniseriesList) {
        m.playPreview();
        cout << "-------------------------\n";
    }
}

class Review;

template <typename T>
class Repository {
private:
    vector<T> records;
    string numeRepertoriu;

public:
    Repository(const string& name = "General") : numeRepertoriu(name) {}
    Repository(const Repository& other) = default;
    Repository& operator=(const Repository& other) = default;
    ~Repository() = default;
    void addRecord(const T& newRecord) {
        if (find(records.begin(), records.end(), newRecord) != records.end()) {
            string itemName = "item";
            try {
                itemName = newRecord.getUsername();
                } catch (...) {
                itemName = "unknown item"; }
            throw invalid_argument("Evidenta '" + itemName + "' exista deja in  " + numeRepertoriu + ".");
        }

        records.push_back(newRecord);
        cout << "Evidenta adaugata cu succes in repertoriul:  " << numeRepertoriu << "." << endl;
    }

    void displayAllRecords() const {
        if (records.empty()) {
            cout << "Nu exista evidente in: " << numeRepertoriu << "." << endl;
            return;
        }
        cout << "--- " << numeRepertoriu << " Records ---" << endl;
        int index = 1;
        for (const auto& record : records) {
            cout << index++ << ". " << record << endl;
        }
    }

   template <typename ID_Type>
    T* findRecordById(ID_Type id) {
        for (auto& record : records) {
            try {
                    if (record.getReviewId() == id) {
                    return &record;
                }
            } catch (...) {}
        }
        return nullptr;
    }

    template <typename ID_Type>
    bool removeRecordById(ID_Type id) {
        auto initial_size = records.size();
        records.erase(remove_if(records.begin(), records.end(),
            [&](const T& record) {
                try {
                return record.getReviewId() == id;
                } catch (...) {
                    return false;
                }
            }),
        records.end());
        return records.size() < initial_size;
    }

    vector<T>& getRecords() { return records; }
};
class Review {
    static int generator;
    const int reviewId;
    int programId;
    string username;
    string comment;
    float score;
    float* noteDetaliate;
    int nrNote;

public:

    Review(int progId, const string& user, const string& comm, float s, const float* note, int nr) :reviewId(++generator),programId(progId), username(user),comment(comm),score(s),nrNote(nr)
    {
        if (nrNote > 0) {
            noteDetaliate = new float[nrNote];
            for (int i = 0; i < nrNote; i++)
                noteDetaliate[i] = note[i];
        } else {
            noteDetaliate = nullptr;
        }
    }


    Review() : reviewId(++generator),programId(-1), username("Anonim"), comment("N/A"),score(0.0f), noteDetaliate(nullptr), nrNote(0) { }

    Review(const Review& other) :reviewId(other.reviewId), programId(other.programId),username(other.username),comment(other.comment),score(other.score),nrNote(other.nrNote)
    {
        if (nrNote > 0) {
            noteDetaliate = new float[nrNote];
            for (int i = 0; i < nrNote; ++i)
                noteDetaliate[i] = other.noteDetaliate[i];
        } else {
            noteDetaliate = nullptr;
        }
    }

    ~Review() {
        delete[] noteDetaliate;
    }

    Review& operator=(const Review& r) {
        if (this != &r) {
            delete[] noteDetaliate;

            programId = r.programId;
            score = r.score;
            nrNote = r.nrNote;
            username = r.username;
            comment = r.comment;

            if (nrNote > 0) {
                noteDetaliate = new float[nrNote];
                for (int i = 0; i < nrNote; i++)
                    noteDetaliate[i] = r.noteDetaliate[i];
            } else {
                noteDetaliate = nullptr;
            }
        }
        return *this;
    }

    bool operator==(const Review& other) const {
        return (username == other.username &&
                comment == other.comment &&
                score == other.score &&
                programId == other.programId);
    }

    Review& operator+=(float x) {
        score += x;
        if (score > 10.0f) score = 10.0f;
        return *this;
    }

    friend Review operator+(Review& r, float x) {
        r.score += x;
        if (r.score > 10.0f) r.score = 10.0f;
        return r;
    }

    Review operator+(float x) {
        this->score += x;
        if (this->score > 10.0f) this->score = 10.0f;
        return *this;
    }

    friend Review operator+(float x, Review& r) {
        r.score += x;
        if (r.score > 10.0f) r.score = 10.0f;
        return r;
    }

    friend Review operator-(Review& r, float x) {
        r.score -= x;
        if (r.score < 0.0f) r.score = 0.0f;
        return r;
    }

    Review operator-(float x) {
        this->score -= x;
        if (this->score < 0.0f) this->score = 0.0f;
        return *this;
    }

    Review& operator-=(float x) {
        this->score -= x;
        if (this->score < 0.0f) this->score = 0.0f;
        return *this;
    }

    Review& operator--() {
        this->score -= 1.0f;
        if (this->score < 0.0f) this->score = 0.0f;
        return *this;
    }

    Review operator--(int) {
        Review copie = *this;
        --(*this);
        return copie;
    }
    float& operator[](int index) {
        if (index < 0 || index >= nrNote)
            throw out_of_range("Index invalid pentru note!");
        return noteDetaliate[index];
    }

    friend istream &operator>>(istream &in, Review &r){
        cout << "Introdu numele contului sub care vrei sa lasi o recenzie:" << '\n';
        getline(in >> std::ws, r.username);
        cout << "Introdu ID-ul programului pentru care vrei sa lasi un review:" << '\n';
        in >> r.programId;
        in.ignore();
        cout << "Ce parere ai despre acest program?" << '\n';
        getline(in, r.comment);
        cout << "Ce rating ii dai acestui program (0.0-10.0):" << '\n';
        in >> r.score;

        char ch;
        cout << "Daca programul selectat este serial, doresti sa lasi scoruri pentru fiecare episod?[Y/n]" << '\n';
        in >> ch;
        in.ignore();

        if (ch == 'Y' || ch == 'y') {
            srand(time(0));
            r.nrNote = rand() % 10 + 1;
            delete[] r.noteDetaliate;
            r.noteDetaliate = new float[r.nrNote];

            cout << "Introdu scorurile detaliate pentru " << r.nrNote << " episoade:" << '\n';
            for (int i = 0; i < r.nrNote; i++) {
                cout << "Episodul cu numarul " << (i + 1) << " are scorul de:" << '\n';
                in >> r.noteDetaliate[i];
            }
            in.ignore();
        } else {
            delete[] r.noteDetaliate;
            r.noteDetaliate = nullptr;
            r.nrNote = 0;
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const Review& r) {
        out << "Review ID: " << r.reviewId << '\n';
        out << "Program ID: " << r.programId << '\n';
        out << "User: " << r.username << '\n';
        out << "Scor: " << r.score << '\n';
        out << "Comentariu: " << r.comment << '\n';
        if (r.nrNote > 0) {
            out << "Note detaliate: ";
            for (int i = 0; i < r.nrNote; ++i)
                out << r.noteDetaliate[i] << (i + 1 < r.nrNote ? ", " : "");
            out << '\n';
        }
        return out;
    }

    int getReviewId() const {
        return reviewId; }
    int getProgramId() const {
        return programId; }
    string getUsername() const {
        return username; }
    string getComment() const {
        return comment; }
    float getScore() const {
        return score; }
    int getNrNote() const {
        return nrNote; }
    const float* getNoteDetaliate() const { return noteDetaliate; }


    void setUsername(string newUser) {
        username = newUser;
    }

    void setComment(string newComment) {
        comment = newComment;
    }

    void setScore(float newScore) {
        if (newScore >= 0.0f && newScore <= 10.0f)
            score = newScore;
        else
            throw invalid_argument("Scorul introdus nu este valid!");
    }

    void setNoteDetaliate(const float* notes, int nr) {
        delete[] noteDetaliate;
        nrNote = nr;
        if (nrNote > 0) {
            noteDetaliate = new float[nrNote];
            for (int i = 0; i < nrNote; ++i)
                noteDetaliate[i] = notes[i];
        } else {
            noteDetaliate = nullptr;
        }
    }

};

int Service::generator=1234;
set<Account> Account::listOfAcc;
int Account::nrOfAcc=0;
int Review::generator = 1234;
Repository<Review> reviewRepository("Review Repository");
int Program::generator = 0;
list<Service> Service::listOfServices;
vector<Program> Program::programsList;
vector<Film> Program::filmsList;
vector<Serial> Program::serialsList;
vector<Documentar> Program::documentarsList;
vector <Miniseries> Program::miniseriesList;

int main()
{
    try{
    Program::load("programe.txt");}
    catch(const exception& e)
    {
        cout<<e.what()<<endl;
    }
    auto &menu = Menu::getInstance();
    menu.addItem(1, "Alege serviciul tau preferat de streaming.", [](){
            Service service;
            cout<<"Serviciile disponibile sunt:"<<'\n';
            serviceIn.clear();
            serviceIn.seekg(0, ios::beg);
            char serviciu[MAX_LENGTH];
            int index = 1;
            while(serviceIn.getline(serviciu,MAX_LENGTH)){
                cout<<index<<" -> "<<serviciu<<'\n';
                index++;
            }
            cin>>service;
            if (Service::ServiceExists(service)){
                cout<<"Serviciul a mai fost selectat."<<'\n';
                cout<<"Doresti schimbarea abonamentului(1) sau selectarea altui serviciu(2)?"<<'\n';
                cin>>index;
                cin.get();
                if (index==1){
                Service::SchimbaAbonamentul(service);
                cout<<service;
                }else if(index==2){
                cout<<service<<'\n';
                cin>>service;
                cout<<service<<'\n';
                Service::addServiceToList(service);
                }
            }else{
            cout<<service<<'\n';
            Service::addServiceToList(service);
            }

        });
    menu.addItem(2,"Afiseaza abonamentele active.", [](){
            Service::showAllServices();
        });
    menu.addItem(3, "Anuleaza un abonament.", [](){
            int ID;
            Service::showServicesById();
            cout<<"Selecteaza ID-ul subscriptiei pe care vrei sa o anulezi: ";
            cin>>ID;
            cin.get();
            try{
            Service::deleteServiceById(ID);
            cout<<"Abonamentele active ramase sunt:"<<'\n';
            Service::showAllServices();
            }catch(const exception& e){
                cout<<e.what();
            }

        });
    menu.addItem(4, "Introdu un abonament care vrei sa fie afisat din lista.", [](){
            Service service;
            int index;
            try{
            Service::showAllServices();
            cin>>index;
            cin.get();
            try{
            cout<<service[--index]<<'\n';
            }catch (const exception &e){
            cout<<e.what()<<'\n';
            }
            }catch(const exception& e)
            {
                cout<<e.what()<<endl;
            }
        });
    menu.addItem(5, "Creeaza un cont nou.", [](){
            int index;
            Account acc;
            cin>>acc;
            if (Account::AccountExists(acc)){
                cout<<"Contul introdus deja exista."<<'\n';
                cout<<"Doresti schimbarea contului(1) sau stergerea acestuia(2)?"<<'\n';
                cin>>index;
                cin.get();
                if (index==1){
                Account::showAllAcc();
                cout<<"Introdu parola pentru contul in care vrei sa te loghezi: ";
                char parola[MAX_LENGTH];
                cin>>parola;
                cin.get();
                int ok=0;
                try{
                    ok=Account::parolaCorecta(parola);
                    if (ok){
                            cout<<"Felicitari, te-ai logat in cont."<<'\n';
                }else{
                    cout<<"Parola introdusa etse gresita!Mai incearca o data."<<'\n';
                }
                }catch (const exception& e){
                    cout<<e.what()<<endl;
                }
                }else if(index==2){
                cout<<"Introdu ID-ul contului pe care vrei sa-l stergi:"<<'\n';
                Account::showAllAccById();
                int id;
                cin>>id;
                cin.get();
                try{
                Account::deleteAcc(id);
                    }catch(const exception& e)
                    {
                        cout<<e.what()<<endl;
                    }
                }
            }else{
            cout<<"Contul a fost adaugat cu succes!"<<'\n';
            Account::addAccToList(acc);
            }
        });
    menu.addItem(6,"Log-in in cont.",[](){
            cout<<"Introdu ID-ul contului in care vrei sa te loghezi."<<'\n';
            Account::showAllAccById();
            int id;
            cin>>id;
            cin.get();
            cout<<"Introdu parola pentru contul cu ID-ul: "<<id<<'\n';
            char parola[MAX_LENGTH];
            cin>>parola;
            int ok=0;
            try{
                ok=Account::parolaCorecta(parola);
                if(ok){
                    cout<<"Felicitari, te-ai logat in cont."<<'\n';
                }else{
                    cout<<"Parola introdusa este gresita!Mai incearca o data."<<'\n';
                }
                }catch(const exception& e){
                    cout<<e.what()<<endl;
                }
            });
    menu.addItem(7,"Afiseaza toate conturile active.",[](){
            Account::showAllAcc();
        });
    menu.addItem(8, "Primeste informatii despre un cont activ.",[](){
            Account account;
            cout<<"Introdu ID-ul contului despre care vrei informatii."<<'\n';
            Account::showAllAcc();
            int index;
            cin>>index;
            cin.get();
            try{
                cout<<account[--index]<<'\n';
            }catch (const exception& e){
            cout<<e.what()<<'\n';
            }
        });
    menu.addItem(9,"Afiseaza lista de programe disponibile.",[](){
            Program::showAllPrograms();
        });
    menu.addItem(10,"Cauta un program in lista cu programe.",[](){
            char nume[MAX_LENGTH];
            cout<<"Numele programului pe care vrei sa-l cauti este: "<<'\n';
            cin.getline(nume,MAX_LENGTH);
            if(Program::ProgramExists(nume)){
                cout<<"Ai selectat programul cu numele: "<<nume<<'\n';
            }else{
                cout<<"Programul nu a fost gasit!"<<'\n';
            }
        });
    menu.addItem(11,"Afiseaza programele cu rating mai bun in functie de preferintele personale.",[](){
            cout<<"Introdu rating-ul minim pe care-l doresti:"<<'\n';
            float rate;
            cin>>rate;
            Program::afiseazaRatingMaiMare(rate);
        });
    menu.addItem(12,"Daca nu ai gasit un program, poti sa-l adaugi in lista de recomandate.",[](){
            cout<<"Ce fel de tip de program vrei sa adaugi?"<<endl<<"Film/Serial/Documentar/Miniseries"<<endl;
            char program[MAX_LENGTH];
            cin.getline(program, MAX_LENGTH);
            if (!strcmp(program, "Film"))
            {
                Film f;
                cin>>f;
                Program::addFilm(f);
            }else if (!strcmp(program, "Serial"))
            {
                Serial s;
                cin>>s;
                Program::addSerial(s);
            }else if (!strcmp(program,"Documentar")){
                Documentar d;
                cin>>d;
                Program::addDocumentar(d);
            }else if (!strcmp(program,"Miniseries")){
                Miniseries m;
                cin>>m;
                Program::addMiniseries(m);
            }else {
                Program p;
                        cin>>p;
            Program::addProgram(p);
            }
        });
    menu.addItem(13,"Adauga un review pentru programul tau preferat.",[](){
            cout<<"Selecteaza ID-ul programului pentru care vrei sa lasi un review:"<<endl;
            Program::showAllProgramsById();
            int progId;
            cin>>progId;
            cin.ignore();
            Review r;
            cin>>r;
            try {
                  reviewRepository.addRecord(r);
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
        });
    menu.addItem(14,"Afiseaza toate review-urile lasate de catre tine.",[](){
            reviewRepository.displayAllRecords();
        });
    menu.addItem(15,"Sterge un review scris.",[](){
            cout<<"Selecteaza Id-ul unui review pe care vrei sa-l stergi:"<<'\n';
            reviewRepository.displayAllRecords();
            int id;
            cin>>id;
            cin.get();
            reviewRepository.removeRecordById(id);
            cout<<"Review-urile ramase sunt:"<<'\n';
            reviewRepository.displayAllRecords();
        });
    menu.addItem(16,"Afiseaza preview-urile programelor.",[](){
            Program::previewAllPrograms();

        });
    menu.addItem(17,"Afiseaza programul preferat de utilizatori pentru ziua de azi!", [](){
    char title[] = "Twin Peaks";
    char genre[] = "Mystery";
    char director[] = "David Lynch";
    Miniseries* miniserie = new Miniseries(title, genre, 8.8, director, 8, 47.0);

    cout << "Miniseries originala:" << endl;
    cout << *miniserie << endl;
    Film* filmPtr = miniserie;
    cout << "\nTratata ca Film (upcasting):" << endl;
    cout << *filmPtr << endl;
    Program* progPtr = miniserie;
    cout << "\nTratata ca Program (upcasting):" << endl;
    cout << *progPtr << endl;
    cout << "PlayPreview:" << endl;
    filmPtr->playPreview();
    delete miniserie;

        });
    menu.addItem(18,"Urmatoarele programe o sa fie scoase in curand. Vizioneaza-le cat mai poti!", [](){
    vector<Program*> programe;
    char title1[] = "Lost Highway";
    char genre1[] = "Thriller";
    char director1[] = "David Lynch";
    programe.push_back(new Film(title1, genre1, 7.6, director1, 148.0));

    char title2[] = "It";
    char genre2[] = "Horror";
    char director2[] = "Tommy Lee Wallace";
    programe.push_back(new Miniseries(title2, genre2, 7.1, director2, 2, 90.0));

    cout << "Programe stocate ca Program* (upcasting):" << endl;
    for(int i = 0; i < programe.size(); i++) {
        cout << "\nProgram " << (i+1) << ":" << endl;
        cout << "Titlu: " << programe[i]->getTitle() << endl;
        cout << "Tip: " << programe[i]->getType() << endl;

        Film* filmPtr = dynamic_cast<Film*>(programe[i]);//downcast la film
        if(filmPtr) {
            cout << "Este un Film! Durata: " << filmPtr->getDuration() << " minute" << endl;
            cout << "Director: " << filmPtr->getDirector() << endl;
            Miniseries* miniPtr = dynamic_cast<Miniseries*>(filmPtr);//downcast la miniseries
            if(miniPtr) {
                cout << "De fapt este o Miniserie!" << endl;
                cout << "Numarul de episoade: " << miniPtr->getNrEpisodes() << endl;
                cout << "Durata per episod: " << miniPtr->getEpisodeDuration() << " minute" << endl;
            }
        }
        cout << "Preview polimorfic:" << endl;
        Previewable* previewPtr = dynamic_cast<Previewable*>(programe[i]);
        if(previewPtr) {
            previewPtr->playPreview();
        }
    }
        for(auto prog : programe) {
            delete prog;
        }
        });
    menu.addItem(0,"EXIT",[](){
            cout << "Te asteptam data viitoare cu filmele si serialele tale favorite!\n";
            exit(0);
        });
    while (true) {
            cout<<"====================="<<endl;
            cout<<"Serviciu de Streaming"<<endl;
            cout<<"====================="<<endl;
            cout<<"--------MENIU--------"<<endl;
            cout<<"====================="<<endl;
            menu.showAndExecute();
    }

    return 0;
}
