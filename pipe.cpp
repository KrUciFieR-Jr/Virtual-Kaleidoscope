#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
int size1=700;
using namespace cv;
using namespace std;
Mat rotate(Mat source,int angle){
    Mat dst;
    Mat empty(size1,size1,CV_8UC3,Scalar(0,0,0));
    Point2f src_center(source.cols/2.0F, source.rows/2.0F);
    Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);
    warpAffine(source, dst, rot_mat, source.size());
    return dst;
}
Mat cuts(Mat img,Mat kal1, Mat kal2,Mat rotated, Mat add,Mat fliped_add,int count,int cut_number){
    Mat gray,edge;
    count = count %1000;
    if(cut_number==8){
        for (int j = 3*img.cols/8; j <img.cols/2; ++j)
        {   
       for(int i=0;i<img.rows/2;i++){
        if(i < 4*j-3*img.cols/2){
            kal1.at<Vec3b>(i,j)=img.at<Vec3b>(i, j);            
        } }
       }

        flip(kal1,kal2,1);
        addWeighted(kal1,1,kal2,1,0,add);
        flip(add,fliped_add,0);
        addWeighted(fliped_add,1,add,1,0,add);
        rotated = rotate(add,90);
        addWeighted(rotated,1,add,1,0,add);
        rotated = rotate(rotated,-30);
        addWeighted(rotated,1,add,1,0,add);
        rotated = rotate(rotated,-30);
        addWeighted(rotated,1,add,1,0,add);
        rotated = rotate(rotated,-60);
        addWeighted(rotated,1,add,1,0,add);
        rotated = rotate(rotated,-30);
        addWeighted(rotated,1,add,1,0,add);
        if(count<=10||count>=140){
        // cout <<  "Hello" << endl;
        cvtColor(add, gray, CV_BGR2GRAY);
        Canny( gray, edge, 50, 150, 3);
        edge.convertTo(add, CV_8U);
        }

        return add;
    }
    
    if (cut_number==16)
    { 
               for (int i = 0; i <=img.rows; ++i)
       {
        for (int j =7*img.cols/16; j<img.cols/2; ++j)
        {
            if (i <= 8*j-7*img.cols/2)
            {
            kal1.at<Vec3b>(i,j)=img.at<Vec3b>(i, j);            
            }
        }
       }
    

        
        flip(kal1,kal2,1);
        // transpose(kal1,kal1);
        addWeighted(kal1,1,kal2,1,0,add);
        flip(add,fliped_add,0);
        addWeighted(fliped_add,1,add,1,0,add);
        rotated = rotate(add,15);
        for (int i = 0; i < 10; ++i)
        {
            addWeighted(rotated,1,add,1,0,add);
            rotated = rotate(rotated,15);

        }
        addWeighted(rotated,1,add,1,0,add);
        if(count<160|| count >590){
        // cout <<  "Hello" << endl;
        cvtColor(add, gray, CV_BGR2GRAY);
        Canny( gray, edge, 50, 150, 3);
        edge.convertTo(add, CV_8U);
        }
        return add;

    }



}
int main()
{
    Mat img,cap_image,img2,kal1(size1,size1,CV_8UC3,Scalar(0,0,0));
    Mat kal2,add,fliped_add,rotated;
    bool Cap_opened;
    int count=1;
    ostringstream str1,count_str;
    VideoCapture cap(0);
	cvNamedWindow("Kaleidoscope",CV_WINDOW_NORMAL);
	// cvSetWindowProperty("Kaleidoscope",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
	// cap.open("http://192.168.0./cam_pic_new.php?x.mjpeg");
    int store_point=301;
    for(;;)
    {
        cout <<  store_point << endl;
    if (cap.isOpened() & store_point%300!=0)
    {
        cap>>cap_image;
        //Resize
       resize(cap_image,cap_image,Size(size1,size1));
       // str1.clear();
       str1 << store_point;
       imwrite("buffer_store//"+str1.str()+".jpg", cap_image);
       cout<< "Storing in buffer_store//"+str1.str()+".jpg"<<endl;
       Cap_opened = true;
       str1.str("");

    }
        count_str << count;
        cout<< "buffer_store//"+count_str.str()+".jpg"<<endl;
        img=imread("buffer_store//"+count_str.str()+".jpg");
        count_str.str("");
        // cout<< count+" Image Processing" << endl;
        resize(img,img,Size(size1,size1));
        if(count%300<=150){
            kal1 =0;
            add=cuts(img,kal1,kal2,rotated,add,fliped_add,count,8);
        }
        if(count%300>150){
            kal1=0;
            add=cuts(img,kal1,kal2,rotated,add,fliped_add,count,16);
            if(count%300==299){
            if(store_point%300==299){
                count =600-count%600-1;
                store_point=600-store_point%600-1;
            }
            else{
                if(store_point>300){
                    count =0;
                }
                else{
                    count=300;
                }
                
            }
        }
        }
        if(Cap_opened){
            store_point++;
        }
        count++;

        imshow("img",img);
        imshow("Kaleidoscope",add);
        waitKey(1);
    }

    return 1;

}