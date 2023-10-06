#include "datastruc.h"
#include "drivers.h"
#include "users.h"
#include "glib.h"
#include "rides.h"


struct data {
    GArray *drivers;    //1
    GHashTable *users;  //1
    GList *ordDrivers;  //2
    GList *ordUsers;    //3

    GList *rides;   //5 8 9
    GHashTable *ridesCity; //4 6
    GHashTable *topDrivCity; //7
};

DATA init() {
    DATA d;
    d = malloc(sizeof(struct data));
  
    d->drivers = g_array_new(FALSE, TRUE, sizeof(DRIVERS)); 
    d->users = g_hash_table_new(g_str_hash, g_str_equal);  
    d->ordDrivers = NULL; 
    d->ordUsers = NULL; 

    d->ridesCity = g_hash_table_new(g_str_hash, g_str_equal);
    d->rides = NULL; 
    d->topDrivCity = g_hash_table_new(g_str_hash, g_str_equal);

    return d;
}

void cleanStruct(DATA d) {
    GList *c;

    //users
    c = g_hash_table_get_keys(d->users);
    while (c != NULL) {
        free(c->data);
        c = g_list_next(c);
    }
    g_list_free(c);
    c = g_hash_table_get_values(d->users);
    while (c != NULL) {
        free(c->data);
        c = g_list_next(c);
    }
    g_list_free(c);
    g_hash_table_destroy(d->users);

    //drivers
    for (unsigned int i = 0; i < d->drivers->len; i++)
        free(g_array_index(d->drivers, DRIVERS, i));
    g_array_free(d->drivers, TRUE);

    //ordDrivers
    g_list_free(d->ordDrivers);
    //ordUsers
    g_list_free(d->ordUsers);

    //rides
    c = d->rides;
    while (c != NULL) {
        free(c->data);
        c = g_list_next(c);
    }
    g_list_free(d->rides);

    //ridesCity
    c = g_hash_table_get_keys(d->ridesCity);
    while (c != NULL) {
        free(c->data);
        c = g_list_next(c);
    }
    g_list_free(c);
    c = g_hash_table_get_values(d->ridesCity);
    while (c != NULL) {
        g_list_free(c->data);
        c = g_list_next(c);
    }
    g_list_free(c);
    g_hash_table_destroy(d->ridesCity);

    //topDrivCity
    c = g_hash_table_get_keys(d->topDrivCity);
    while (c != NULL) {
        free(c->data);
        c = g_list_next(c);
    }
    g_list_free(c);
    c = g_hash_table_get_values(d->topDrivCity);
    while (c != NULL) {
        g_list_free_full(c->data, free);
        c = g_list_next(c);
    }
    g_list_free(c);
    g_hash_table_destroy(d->topDrivCity);

    free(d);
}

void insertDriver(int id, DRIVERS nd, DATA d) {
    g_array_insert_val(d->drivers, id, nd);
}

void insertUser(char username[], USERS nu, DATA d) {
    g_hash_table_insert (d->users, username, nu);
}

void insertRide(RIDES nr, DATA d) {
    char *cityStr = getCityR(nr);
    //ridesCity
    GList *city = g_hash_table_lookup(d->ridesCity, cityStr);
    if (city == NULL) {
        city = g_list_prepend(city, nr);
        g_hash_table_insert(d->ridesCity, getCityR(nr), city);
    } else {
        city = g_list_prepend(city, nr);
        g_hash_table_insert(d->ridesCity, cityStr, city);
    }

    //rides
    d->rides = g_list_prepend(d->rides, nr);

    free(cityStr);
}

DRIVERS lookUpDriver(int id, DATA d) {
    if (d->drivers->len < id) return NULL;
    return g_array_index(d->drivers, DRIVERS, id);
}

USERS lookUpUser(char username[], DATA d) {
    return g_hash_table_lookup (d->users, username);
}

GList *getOrdUsers(DATA d) {
    return d->ordUsers;
}

GList *getOrdDrivers(DATA d) {
    return d->ordDrivers;
}

GList *lookUpCityRides(char city[], DATA d) {
    return g_hash_table_lookup (d->ridesCity, city);
}

GList *lookUpTopDrivRides(char city[], DATA d) {
    return g_hash_table_lookup (d->topDrivCity, city);
}

GList *getRides(DATA d) {
    return d->rides;
}

int getArraySize(DATA d) {
    return d->drivers->len;
}

void createLists(DATA d) {
    //ordDrivers
    DRIVERS nd;
    for (unsigned int i = 0; i < d->drivers->len; i++) {
        nd = g_array_index(d->drivers, DRIVERS, i);
        if (nd != NULL) d->ordDrivers = g_list_prepend(d->ordDrivers, nd);
    }
    d->ordDrivers = g_list_sort(d->ordDrivers, depenDrivers);
    
    //ordUsers
    d->ordUsers = g_hash_table_get_values(d->users);
    d->ordUsers = g_list_sort(d->ordUsers, depenUsers);

    //rides
    d->rides = g_list_sort(d->rides, depenDateRides);

    //topDrivCity
    char *city;
    GList *list, *ls, *dl = NULL; 
    RIDES r, ra, rd;
    DriverPC dpc = NULL;
    list = g_hash_table_get_values(d->ridesCity);
    while (list != NULL) {
        ls = (GList *)list->data;
        r = (RIDES)ls->data;
        city = getCityR(r);
        ls = g_list_sort(ls, depenIdRides);

        while(ls->next != NULL) {
            ra = (RIDES)ls->data;
            rd = (RIDES)ls->next->data;

            if(dpc == NULL) dpc = newDPC(getDriverR(ra));
            updateDPC(dpc, getScoreDriverR(ra));

            if (getIdD(getDriverR(ra)) != getIdD(getDriverR(rd))) {
                dl = g_list_prepend(dl, dpc);
                dpc = newDPC(getDriverR(rd));
            }

            ls = g_list_next(ls);
        }
        dl = g_list_sort(dl, depenCity);
        g_hash_table_insert(d->topDrivCity, city, dl);
        dl = NULL;

        list = g_list_next(list);
    }
    g_list_free(g_list_first(list));

    //ridesCity
    list = g_hash_table_get_values(d->ridesCity);
    while (list != NULL) {
        ls = (GList *)list->data;
        r = (RIDES)ls->data;
        city = getCityR(r);
        ls = g_list_sort(g_list_first(ls), depenDateRides);
        g_hash_table_insert(d->ridesCity, city, ls);
        free(city);
        list = g_list_next(list);
    }
    g_list_free(g_list_first(list));


}