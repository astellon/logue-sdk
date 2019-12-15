#ifndef __SIMPLESIN_H__
#define __SIMPLESIN_H__

#define MAX_NUM_PARAMS 6

#define FAUSTFLOAT float

typedef struct Param{
  FAUSTFLOAT* zone;
  FAUSTFLOAT init;
  FAUSTFLOAT min;
  FAUSTFLOAT max;
  FAUSTFLOAT step;
} Param;

typedef struct NutektUIInterface{
  Param params[MAX_NUM_PARAMS];
  int num_params;
} NutektUIInterface;

static void openTabBoxNutekt(void* interface, const char* label) {};
static void openHorizontalBoxNutekt(void* interface, const char* label) {};
static void openVerticalBoxNutekt(void* interface, const char* label) {};
static void closeBoxNutekt(void* interface) {};
static void addButtonNutekt(void* interface, const char* label, FAUSTFLOAT* zone) {};
static void addCheckButtonNutekt(void* interface, const char* label, FAUSTFLOAT* zone) {};

static void addNumEntryNutekt(void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
  NutektUIInterface* nutekt = (NutektUIInterface*)interface;
  nutekt->params[nutekt->num_params].zone = zone;
  nutekt->params[nutekt->num_params].init = init;
  nutekt->params[nutekt->num_params].min  = min;
  nutekt->params[nutekt->num_params].max  = max;
  nutekt->params[nutekt->num_params].step = step;
  nutekt->num_params++;
};

static void addVerticalSliderNutekt(void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
  addNumEntryNutekt(interface, label, zone, init, min, max, step);
}

static void addHorizontalSliderNutekt(void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
  addNumEntryNutekt(interface, label, zone, init, min, max, step);
}

static void addHorizontalBargraphNutekt(void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {};
static void addVerticalBargraphNutekt(void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {};
static void declareNutekt(void* interface, FAUSTFLOAT* zone, const char* key, const char* value) {};

#endif