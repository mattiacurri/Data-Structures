#ifndef RATING_H
#define RATING_H

#include "../linkedList.h"

using std::string;

class rating {
public:
    string utente;
    string prodotto;
    int rating;
};

class recommender {
public:
    void insert(string user, string item, int new_rating);

    double meanUser(string user);

    double meanItem(string item);

    LinkedList<string> rated(string user);

    LinkedList<string> common(string user1, string user2);

    int commonEqual(string user1, string user2);

    // accessorie
    LinkedList<string> productRatings(string product);

private:
    LinkedList<rating> ratings;
};

void recommender::insert(string user, string item, int new_rating) {
    rating r;
    r.utente = user;
    r.prodotto = item;
    r.rating = new_rating;
    if (ratings.empty()) {
        ratings.headInsert(r);
    } else {
        bool isNewRating = true;
        LinkedList<rating>::position p = ratings.begin();
        while (!ratings.end(p) && isNewRating) {
            if (ratings.read(p).utente == user && ratings.read(p).prodotto == item) {
                isNewRating = false;
            }
            p = ratings.next(p);
        }
        if (isNewRating) {
            ratings.headInsert(r);
        }
    }
}

double recommender::meanUser(string user) {
    LinkedList<rating>::position r = ratings.begin();
    int sum = 0;
    int size = 0;
    while (!ratings.end(r)) {
        if (ratings.read(r).utente == user) {
            sum += ratings.read(r).rating;
            size++;
        }
        r = ratings.next(r);
    }
    return (double) sum / size;
}

double recommender::meanItem(string item) {
    LinkedList<rating>::position r = ratings.begin();
    int sum = 0;
    int size = 0;
    while (!ratings.end(r)) {
        if (ratings.read(r).prodotto == item) {
            sum += ratings.read(r).rating;
            size++;
        }
        r = ratings.next(r);
    }
    return (double) sum / size;
}

LinkedList<string> recommender::rated(string user) {
    LinkedList<rating>::position r = ratings.begin();
    LinkedList<string> ratedByUser;
    while (!ratings.end(r)) {
        if (ratings.read(r).utente == user) {
            ratedByUser.headInsert(ratings.read(r).prodotto);
        }
        r = ratings.next(r);

    }
    return ratedByUser;
}

LinkedList<string> recommender::common(string user1, string user2) {
    LinkedList<string> ratedByUser1 = rated(user1);
    LinkedList<string> ratedByUser2 = rated(user2);
    LinkedList<string> commonRated;
    LinkedList<string>::position r1 = ratedByUser1.begin();
    LinkedList<string>::position r2;
    while (!ratedByUser1.end(r1)) {
        r2 = ratedByUser2.begin();
        while (!ratedByUser2.end(r2)) {
            if (ratedByUser1.read(r1) == ratedByUser2.read(r2)) {
                commonRated.headInsert(ratedByUser1.read(r2));
                ratedByUser1.erase(r1);
                ratedByUser2.erase(r2);
            }
            r2 = ratedByUser2.next(r2);
        }
        r1 = ratedByUser1.next(r1);
    }

    return commonRated;
}

LinkedList<string> recommender::productRatings(string product) {
    LinkedList<rating>::position r = ratings.begin();
    LinkedList<string> ratedByProduct;
    while (!ratings.end(r)) {
        if (ratings.read(r).prodotto == product) {
            ratedByProduct.headInsert(ratings.read(r).utente);
        }
        r = ratings.next(r);
    }
    return ratedByProduct;
}

int recommender::commonEqual(string user1, string user2) {
    int u1 = 0;
    int u2 = -1;
    int counter = 0;
    LinkedList<string> commonRated = common(user1, user2);
    LinkedList<rating>::position p = ratings.begin();
    LinkedList<string>::position p2 = commonRated.begin();
    while (!commonRated.end(p2)) {
        u1 = -1;
        u2 = 0;
        p = ratings.begin();
        while (!ratings.end(p)) {
            if (ratings.read(p).utente == user1 && ratings.read(p).prodotto == commonRated.read(p2)) {
                u1 = ratings.read(p).rating;
            } else if (ratings.read(p).utente == user2 && ratings.read(p).prodotto == commonRated.read(p2)) {
                u2 = ratings.read(p).rating;
            }
            if (u1 == u2) {
                counter++;
                break;
            }
            p = ratings.next(p);
        }
        p2 = commonRated.next(p2);
    }
    return counter;
}


#endif //RATING_H
