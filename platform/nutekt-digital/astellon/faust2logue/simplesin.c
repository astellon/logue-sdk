/* ------------------------------------------------------------
name: "simplesin"
Code generated with Faust 2.15.11 (https://faust.grame.fr)
Compilation options: -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


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


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 


#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdlib.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
	
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fRec2[2];
	float fRec1[2];
	float fRec0[2];
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)calloc(1, sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "filename", "simplesin");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "simplesin");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 0;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}
int getOutputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
		case 0: {
			rate = 1;
			break;
		}
		default: {
			rate = -1;
			break;
		}
		
	}
	return rate;
	
}

void classInitmydsp(int samplingFreq) {
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)440.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iVec0[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec2[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec1[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec0[l3] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = (6.28318548f / min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq)));
	
}

void instanceInitmydsp(mydsp* dsp, int samplingFreq) {
	instanceConstantsmydsp(dsp, samplingFreq);
	instanceResetUserInterfacemydsp(dsp);
	instanceClearmydsp(dsp);
}

void initmydsp(mydsp* dsp, int samplingFreq) {
	classInitmydsp(samplingFreq);
	instanceInitmydsp(dsp, samplingFreq);
}

void buildUserInterfacemydsp(mydsp* dsp, UIGlue* ui_interface) {
	ui_interface->openVerticalBox(ui_interface->uiInterface, "simplesin");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "frequency", &dsp->fHslider0, 440.0f, 0.0f, 5000.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (dsp->fConst0 * (float)dsp->fHslider0);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			dsp->fRec2[0] = (dsp->fRec2[1] + (fSlow0 * (0.0f - dsp->fRec0[1])));
			dsp->fRec1[0] = ((fSlow0 * dsp->fRec2[0]) + ((float)(1 - dsp->iVec0[1]) + dsp->fRec1[1]));
			dsp->fRec0[0] = dsp->fRec1[0];
			output0[i] = (FAUSTFLOAT)dsp->fRec0[0];
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


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

#endif
