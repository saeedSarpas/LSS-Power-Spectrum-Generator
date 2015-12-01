//-----------------------------------------------------------------------------
// NUMBER OF GRID BLOCKS ALONG EACH AXIS
//-----------------------------------------------------------------------------
int NUM_GRID_IN_EACH_AXIS = 256;

//-----------------------------------------------------------------------------
// NUMBER OF BINS IN FOURIER SPACE FOR POWER SPECTRUM
//-----------------------------------------------------------------------------
int NUM_OF_BINS = 30;

//-----------------------------------------------------------------------------
// STRUCTURED INPUT DATA OF THE FIELD BASED ON THE DATA STRUCTURE (OUTPUT OF
// THE 1ST STEP)
//-----------------------------------------------------------------------------
int STR_LEN = 256;
char IN_FILENAME[2][256] = {"", "HaloTab_Run1.0.1_FOF.txt"};
char IN_NICKS[2][256] = {"random", "HaloTab"};
int IN_ARR_LEN = 2;

//-----------------------------------------------------------------------------
// CONFIG FILE EXTENSION. THIS FILE CONTAINS NUMBER OF PARTICLES AND THE LENGTH
// OF THE FIELD
//-----------------------------------------------------------------------------
char CONFIG_EXT[] = ".conf";

//-----------------------------------------------------------------------------
// CONFIG FILE STRUCTURE
//-----------------------------------------------------------------------------
struct config {
	int NumPart;
	double BoxLength;
} *C;

//-----------------------------------------------------------------------------
// GRIDING ALGORITHM POSTFIX
//-----------------------------------------------------------------------------
char NGP_POSTFIX[] = "ngp";
char CIC_POSTFIX[] = "cic";
char TSC_POSTFIX[] = "tsc";

//-----------------------------------------------------------------------------
// DATA STRUCTURE
// Be cautious, changing this structure leads to the lots of changes in
// different functions
//-----------------------------------------------------------------------------
struct particle_data {
	double Pos[3];
	double Mass;
} *P;
