
/************************************************************************
 ************************************************************************
    FAUST Architecture File

    this is a copy from faust/architecture/pure.c in grame-cncm/faust
    Copyright (C) 2009-2011 Albert Graef <Dr.Graef@t-online.de>

    and modified by Astellon
************************************************************************
************************************************************************/

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

/* Define FAUSTFLOAT so that audio buffers and control values are always
   represented as double pointers. */

#define FAUSTFLOAT float

// index of parameter for note frequency
#ifndef PITCH_INDEX
#define PITCH_INDEX 0
#endif

#define BUFFER_SIZE 32

#include "buffer_ops.h"
#include "userosc.h"

#include "nutekt.h"


//----------------------------------------------------------------------------
//  Abstract user interface
//----------------------------------------------------------------------------

// -- layout groups

typedef void (* openTabBoxFun) (void* interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* interface, const char* label);
typedef void (* openVerticalBoxFun) (void* interface, const char* label);
typedef void (* closeBoxFun) (void* interface);

// -- active widgets

typedef void (* addButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive display widgets

typedef void (* addHorizontalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

typedef void (* declareFun) (void* interface, FAUSTFLOAT* zone, const char* key, const char* value);

typedef struct {
  void* uiInterface;
  openTabBoxFun openTabBox;
  openHorizontalBoxFun openHorizontalBox;
  openVerticalBoxFun openVerticalBox;
  closeBoxFun closeBox;
  addButtonFun addButton;
  addCheckButtonFun addCheckButton;
  addVerticalSliderFun addVerticalSlider;
  addHorizontalSliderFun addHorizontalSlider;
  addNumEntryFun addNumEntry;
  addHorizontalBargraphFun addHorizontalBargraph;
  addVerticalBargraphFun addVerticalBargraph;
  declareFun declare;
} UIGlue;

typedef void (* metaDeclareFun) (void*, const char* key, const char* value);

typedef struct {
  void *metaInterface;
  metaDeclareFun declare;
} MetaGlue;

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

static UIGlue ui;
static NutektUIInterface interface;
static FAUSTCLASS simplesin;
static float buffer[BUFFER_SIZE];

void OSC_INIT(uint32_t platform, uint32_t api)
{
  initmydsp(&simplesin, k_samplerate);

  interface.num_params = 0;
  ui.uiInterface = &interface;
  ui.openTabBox = openTabBoxNutekt;
  ui.openHorizontalBox = openHorizontalBoxNutekt;
  ui.openVerticalBox = openVerticalBoxNutekt;
  ui.closeBox = closeBoxNutekt;
  ui.addButton = addButtonNutekt;
  ui.addCheckButton = addCheckButtonNutekt;
  ui.addVerticalSlider = addVerticalSliderNutekt;
  ui.addHorizontalSlider = addHorizontalSliderNutekt;
  ui.addNumEntry = addNumEntryNutekt;
  ui.addHorizontalBargraph = addHorizontalBargraphNutekt;
  ui.addVerticalBargraph = addVerticalBargraphNutekt;
  ui.declare = declareNutekt;

  buildUserInterfacemydsp(&simplesin, &ui);
}

void OSC_CYCLE(const user_osc_param_t * const params,
               int32_t *yn,
               const uint32_t frames)
{
  q31_t* __restrict y = (q31_t *)yn;
  float* ptr = buffer;

  int read = 0;

  while (read < frames) {
    int num_to_read = min(frames - read, BUFFER_SIZE);

    computemydsp(&simplesin, num_to_read, NULL, &ptr);
    buf_f32_to_q31(ptr, y + read, num_to_read);

    read += num_to_read;
  }
}

void OSC_NOTEON(const user_osc_param_t * const params)
{
  *(interface.params[PITCH_INDEX].zone) = osc_notehzf((params->pitch)>>8);
}

void OSC_NOTEOFF(const user_osc_param_t * const params)
{
  // NOTE OFF
}

void OSC_PARAM(uint16_t index, uint16_t value)
{
  if (index != PITCH_INDEX && index < interface.num_params) {
    Param p = interface.params[index];
    *(p.zone) = linintf(value * 0.01f, p.min, p.max);
  }
}