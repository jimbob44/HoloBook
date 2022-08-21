
#include "HoloBook.h"
//#include "main.h"



void getScreenResolution(int &width, int &height) {
#if WIN32
    width  = (int) GetSystemMetrics(SM_CXSCREEN);
    height = (int) GetSystemMetrics(SM_CYSCREEN);
#else
    Display* disp = XOpenDisplay(NULL);
    Screen*  scrn = DefaultScreenOfDisplay(disp);
    width  = scrn->width;
    height = scrn->height;
#endif
}


Mat rotate(Mat src, double angle)
{
    Mat dst;

    Point2f center((src.cols - 1)/2.0, (src.rows-1)/2.0);
    Mat r = getRotationMatrix2D(center, angle, 1.0);
    Rect2f bbox = RotatedRect(Point2f(), src.size(), angle).boundingRect2f();

    r.at<double>(0,2) += bbox.width/2.0 - src.cols/2.0;
    r.at<double>(1,2) += bbox.height/2.0 - src.rows/2.0;


    warpAffine(src, dst, r, bbox.size());
    return dst;
}

vector<string> get_directories(const string& s)
{
    vector<string> r;
    for(auto& p : experimental::filesystem::directory_iterator(s))
            r.push_back(p.path().string());


    return r;
}

struct command{
    int op1; //integer indicating what to do
    String op2;
    String op3;

};


//Global Variables
deque<command> commandList;

mutex globalMutex1;
mutex globalMutex2;
mutex globalMutex3;
mutex globalMutex4;

bool globalQuit = false;

string globalQuitPage = "11"; // this page number will cause all threads to quit and exit the program

string PageNo = "0";

string rootFolder ( "/home/james/Documents/HoloBook/Books/" );

string bookFolder;

string imageNameBase("test-" );


int screenWidth;
int screenHeight;



//shared memory functions

void addToCommandList(command c)
{
// this function add a command to command list to be acted upon by the main thread
std::lock_guard<std::mutex> guard(globalMutex1);


if(commandList.size() < MAX_COMMAND_LIST_SIZE)
    {

    commandList.push_front(c);

    }
}

command popCommandList()
{
std::lock_guard<std::mutex> guard(globalMutex1);
command c;


c = commandList.back();

commandList.pop_back();



return c;


}

void updatePage(string s)
{

std::lock_guard<std::mutex> guard(globalMutex4);

PageNo = s;

}

string getPage()
{
std::lock_guard<std::mutex> guard(globalMutex4);

return PageNo;

}

void programOutput(string s)
{

std::lock_guard<std::mutex> guard(globalMutex2);

cout << s << endl;

}

void programOutput(string s, bool f)
{

string printstr;

std::lock_guard<std::mutex> guard(globalMutex2);



if (f)
    printstr = "\r"+s;
else
    printstr = s;


printf(printstr.c_str());
fflush(stdout);


}


//thread functions
void bookSelector()
{
 vector<string> bookList;

string e;

bookList = get_directories(rootFolder); //list all the folders in the root directory

//iterator here to output possible books

int n = 1;
unsigned int localPageNo;
unsigned int currentPage;

deque<string> bookNames;

for (auto & element : bookList) {
    e = element.substr(rootFolder.length(),element.length() - rootFolder.length());
    bookNames.push_back(e);
    e = to_string(n) + " " + e;
    e += "\n";
    programOutput(e);
    n++;
}


int j = BOOK_SELECTOR_TIMER_COUNT;

while(j !=0 )
{
    localPageNo = stoi(getPage());

    sleep(1);
    if(localPageNo <= bookList.size() && localPageNo != 0)
    {
        bookFolder = bookList.at(localPageNo-1)  + "/";
        programOutput("Selected Book: " + bookNames.at(localPageNo-1) + " Opening Book in: " + to_string(j) + " seconds \r",true);


        if(localPageNo ==  currentPage)
            j--;
        else
            j = BOOK_SELECTOR_TIMER_COUNT;

        currentPage = localPageNo;
    }
}

}

void quitAllThreads()
{
std::lock_guard<std::mutex> guard(globalMutex3);

globalQuit = true;

}


void pageScan()
{
//this thread continously scans the pages and updates the command list accordingly
    unsigned int maxbufsize = 2048;
    char retbuf[maxbufsize];

    #ifdef PI //different method used on the PI for the return string due to architecture;
    int np;
    int sizeofscan;
    #endif // PI

    string CurrentPage = "5";
    string QuitPage = "10";

    string localPageNo;

    size_t stringpos;

    command c;

    c.op1 = 1; //update dislay
    c.op2 = ""; // displayed page number
    c.op3 = ""; // unused

    bool localQuit = false;


    while(!localQuit && !globalQuit)
    {

        #ifdef PI
        sizeofscan = QRCodeScan(maxbufsize,retbuf);
        #else
        QRCodeScan(maxbufsize,retbuf);
        #endif

        //concatanate the page number with the image string to get the right page number
        // ImageName = ImageName & scannedString
        string scannedString(retbuf);


        stringpos = scannedString.find("Page");



        if ((stringpos  != string::npos) && (stringpos == 0)) // the scanned string contains page
        {
            //extract the page number
            localPageNo = scannedString.substr(4,SCAN_NO); // return all characters until end of string

            #ifdef PI
            np = stoi(PageNo);
            localPageNo = to_string(np);
            #endif // PI


        }


        if(QuitPage.compare(getPage()) == 0)
        {
            quitAllThreads(); // if the code sees the
            programOutput("quit was executed from scan thread");
        }
        if(getPage().compare(CurrentPage) !=0)
        { // If the page has changed put a command in the command list to update display

          //code here to update commandlist global variable
            programOutput("Page number has changed from " + CurrentPage + " to " + localPageNo + "\n");

            updatePage(localPageNo);

            c.op2 = localPageNo;

            addToCommandList(c);


        }


        CurrentPage = localPageNo;

    }

}

//main display thread

void displayPages()
{

    Mat image;

    unsigned int n = 0;
    double aspectRatio;
    string imageName;
    Mat image2;
    string npStr;
    int np;

    command c;

    bool localQuit = false;
    bool doublepagemode = false;
    bool rotateimage = true;

    while(!localQuit && !globalQuit)
    {

     if(!commandList.empty())
        {
                        //process commmands

                c = popCommandList();

                    switch(c.op1)
                    {
                        case 1:
                             // display page image
                             imageName = bookFolder + imageNameBase + c.op2 + ".jpg";
                        break;
                        default:
                        break;
                    }

                programOutput(imageName);



                image = imread( samples::findFile( imageName ), IMREAD_COLOR );
                if(doublepagemode)  //This will execute if in double page mode and will combine the page and the following page
                {
                     // need error checking here to make sure it is valid integer
                    np = stoi(c.op2);
                    np++ ;
                    npStr = imageNameBase + to_string(np) + ".jpg";
                    image2 = imread( samples::findFile(npStr), IMREAD_COLOR );
                    hconcat(image,image2,image);

                }


                if( image.empty() )                      // Check for invalid input
                {
                    cout <<  "Could not open or find the image" << std::endl;
                   // return -1;
                }
                if(n == 0){

                namedWindow( "Display window", WINDOW_NORMAL| WINDOW_FREERATIO); // Create a window for display. Only execute on first loop
                //resizeWindow("Display Window",1366,768);

                setWindowProperty("Display window",WND_PROP_FULLSCREEN,WINDOW_FULLSCREEN);

                }

                if(rotateimage)
                {
			//find the larger of the two dimensions of screen
			//if screen width is larger than height then rotate image and use the width to scale down the height
                    image = rotate(image,90); // Rotate the page for single page mode with small projector
                }

		 // keep the image as normal and scale down based on smaller dimension of width or height
		  // four possible combinations let H = screen height, L = screen width, x = image width, y = image height
		  //
		aspectRatio = (double)image.cols / (double)image.rows;

		programOutput("Image height is: " + to_string(image.rows) + " Image width is: " + to_string(image.cols));
		programOutput("Aspect Ratio is: " + to_string(aspectRatio));

		if(screenWidth >= image.cols) // screen is wider than image
	   	{
		  if(screenHeight >= image.rows)  //screen is taller than image
		  {
			//screen is bigger in boths  dimensions no resize required
	          }
		  else // image is taller than the screen res. resize is required based on screen height
		  {
			resize(image, image, Size(std::round(screenWidth/aspectRatio),screenHeight));


		  }
		}
		else // image is wider than screen
		{
			if(screenHeight >=image.rows) //screen is taller than image
			{

			  resize(image, image, Size(screenWidth,std::round(screenHeight*aspectRatio))); // resize down to screen width

			}
			else //image is taller than screen
			{
				//image is bigger in both dimensions need to find which is the most limiting size and resize based on that
			 	if(image.cols >= image.rows){
					resize(image, image, Size(screenWidth,std::round(screenHeight/aspectRatio)));
					}
				else{
					resize(image, image, Size(std::round(screenHeight*aspectRatio),screenHeight));

					 }
			}
		}

        imshow("Display window", image );                // Show our image inside it.
		waitKey(WAIT_KEY_TIME);
    n++;
   }
  }
}



//main function




int main( int argc, char** argv )
{


getScreenResolution(screenWidth,screenHeight);
cout << "Screen Resolution is Width: " << to_string(screenWidth) << " Pixels Height: " << to_string(screenHeight)<< " Pixels" << std::endl;


std::thread pageScanningThread(pageScan);

std::thread bookSelectorThread(bookSelector);

bookSelectorThread.join();

std::thread displayThread(displayPages);

pageScanningThread.join();

displayThread.join();



return 0;

}
