/* Now double buffered with animation with one PNG dancing.
 */ 

#include <psl1ght/lv2.h>
#include <lv2/process.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <sysutil/video.h>
#include <rsx/gcm.h>
#include <rsx/reality.h>

#include <io/pad.h>

#include <sysmodule/sysmodule.h>
#include <pngdec/pngdec.h>

#include <pngdec/loadpng.h>

#include "pggl.h"

gcmContextData *context; // Context to keep track of the RSX buffer.
VideoResolution res; // Screen Resolution
int currentBuffer = 0;
s32 *buffer[2]; // The buffer we will be drawing into.
int frame = 0;

void waitFlip() { // Block the PPU thread untill the previous flip operation has finished.
	while(gcmGetFlipStatus() != 0) 
		usleep(200);
	gcmResetFlipStatus();
}

void flip(s32 buffer) {
	assert(gcmSetFlip(context, buffer) == 0);
	realityFlushBuffer(context);
	gcmSetWaitFlip(context); // Prevent the RSX from continuing until the flip has finished.
}

// Initilize everything. You can probally skip over this function.
void init_screen() {
	// Allocate a 1Mb buffer, alligned to a 1Mb boundary to be our shared IO memory with the RSX.
	void *host_addr = memalign(1024*1024, 1024*1024);
	assert(host_addr != NULL);

	// Initilise Reality, which sets up the command buffer and shared IO memory
	context = realityInit(0x10000, 1024*1024, host_addr); 
	assert(context != NULL);

	VideoState state;
	assert(videoGetState(0, 0, &state) == 0); // Get the state of the display
	assert(state.state == 0); // Make sure display is enabled

	// Get the current resolution
	assert(videoGetResolution(state.displayMode.resolution, &res) == 0);
	
	// Configure the buffer format to xRGB
	VideoConfiguration vconfig;
	memset(&vconfig, 0, sizeof(VideoConfiguration));
	vconfig.resolution = state.displayMode.resolution;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch = res.width * 4;
	vconfig.aspect=state.displayMode.aspect;

	assert(videoConfigure(0, &vconfig, NULL, 0) == 0);
	assert(videoGetState(0, 0, &state) == 0); 

	s32 buffer_size = 4 * res.width * res.height; // each pixel is 4 bytes
	printf("buffers will be 0x%x bytes\n", buffer_size);
	
	gcmSetFlipMode(GCM_FLIP_VSYNC); // Wait for VSYNC to flip

	// Allocate two buffers for the RSX to draw to the screen (double buffering)
	buffer[0] = rsxMemAlign(16, buffer_size);
	buffer[1] = rsxMemAlign(16, buffer_size);
	assert(buffer[0] != NULL && buffer[1] != NULL);

	u32 offset[2];
	assert(realityAddressToOffset(buffer[0], &offset[0]) == 0);
	assert(realityAddressToOffset(buffer[1], &offset[1]) == 0);
	// Setup the display buffers
	assert(gcmSetDisplayBuffer(0, offset[0], res.width * 4, res.width, res.height) == 0);
	assert(gcmSetDisplayBuffer(1, offset[1], res.width * 4, res.width, res.height) == 0);

	gcmResetFlipStatus();
	flip(1);
}

void setBackColour(int *buffer, s32 colour) {
	s32 i, j;
	for(i = 0; i < res.height; i++) {
		for(j = 0; j < res.width; j++)
			buffer[i* res.width + j] = colour;
	}
}

u32 module_flag;

void unload_modules(){

	if(module_flag & 2)
		SysUnloadModule(SYSMODULE_PNGDEC);

	if(module_flag & 1)
		SysUnloadModule(SYSMODULE_FS);
}

void drawPNG(PngDatas pngin, int IX, int IY) {
		if(pngin.bmp_out) {
			static int x=0,y=0,dx=2,dy=2;
			u32 *scr=  (u32 *) buffer[currentBuffer];
			u32 *png= (u32 *) pngin.bmp_out;
			int n, m;
			if(x < 0) {x=0; dx=1;}
			if(x > (res.width-pngin.width)) {x=(res.width-pngin.width); dx=-2;}
			if(y < 0) {y=0; dy=1;}
			if(y > (res.height-pngin.height)) {y=(res.height-pngin.height); dy=-2;}
			// update x, y coordinates
			x+=IX; y+=IY;
			// update screen buffer from coordinates
			scr+=y*res.width+x;
			// draw PNG
			for(n=0;n<pngin.height;n++) {
				if((y+n)>=res.height) break;
				for(m=0;m<pngin.width;m++) {
					if((x+m)>=res.width) break;
					scr[m]=png[m];
				}
			png+=pngin.wpitch>>2;
			scr+=res.width;
			x = 0;
			y = 0;
			}
		}
}

s32 main(s32 argc, const char* argv[])
{
	PadInfo padinfo;
	PadData paddata;
	int i;
	
	atexit(unload_modules);

	if(SysLoadModule(SYSMODULE_FS)!=0) return 0; else module_flag |=1;

	if(SysLoadModule(SYSMODULE_PNGDEC)!=0) return 0; else module_flag |=2;
	
	init_screen();
	ioPadInit(7);
	init_pggl();
	
	// Ok, everything is setup. Now for the main loop.
	while(1){
		// Check the pads.
		ioPadGetInfo(&padinfo);
		for(i=0; i<MAX_PADS; i++){
			if(padinfo.status[i]){
				ioPadGetData(i, &paddata);
				
				if(paddata.BTN_CROSS){
					sysProcessExitSpawn2("/dev_hdd0/ps3load.self", 0, 0, NULL, 0, 1001, SYS_PROCESS_SPAWN_STACK_SIZE_1M);
				}
			}
			
		}
		waitFlip(); // Wait for the last flip to finish, so we can draw to the old buffer
		setBackColour(buffer[currentBuffer], 0xFFFFFFFF);  // setBuffer to white
		/* PGGL Demo */
		drawInt(frame, 0, res.height - 80);
		draw("PSL1GHT GRAPHICAL\n GAME L1BRARY", (res.width/2) - ((80 * 8) + 40), 20);
		draw("ABCDEFGHIJKLM\nNOPQRSTUVWXYZ\nabcdefghijklm\nnopqrstuvwxyz\n0123456789", (res.width/2) - ((80 * 6) + 40), 500);
		/*			 */
		flip(currentBuffer); // Flip buffer onto screen
		currentBuffer = !currentBuffer;
		if(frame < 1000000)
			frame++;
		else
			frame = 0;
	}
	return 0;
}

