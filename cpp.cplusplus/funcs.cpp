vector<Mat*>* cv_guassian_blur(string file_name, double alpha, int k, int scal)
{
    IplImage* src_img = cvLoadImage(file_name.c_str(), 0);
    if(!src_img) return NULL;

    Mat* src_mat = new Mat(src_img);
    Mat* dst_mat_g, dst_mat_l;
    vector<Mat*>* dst_mats = new vector<Mat*>; 

    try{
        vector<double>* alpha_l = new vector<double>; 
        for(int i = 1; i < 5; ++i) alpha_l->push_back(alpha * i * k); 
        {
            int i_squ = i << 2;
            int al = alpha * i * k;
            GaussianBlur(*src_mat, *dst_mat_g, cv::Size(scal, scal), i_squ, al, cv::BORDER_DEFAULT); 
            Laplacian(*dst_mat_g, *dst_mat_g, dst_mat_g->depth, 1, 1, 0, cv::BORDER_DEFAULT); 
            dst_mats->append(dst_mat_l); 
        }
        delete src_mat, dst_mat_g, dst_mat_l;
    }catch(cv::Exception& e)
    {
        cout << e << endl; 
    }
    return dst_mats;
}

vector<pair<int, int> >* edge_detect(vector<Mat*>* dst_mats)
{
    int width = dst_mats->begin()->rows;
    int height = dst_mats->begin()->cols;
    vector<pair<int, int> >* p_keys = new vector<pair<int, int> >
    try{
        for(int i = 1; i < height - 1; ++i)
        {
            for(int j = 1; j < width - 1; ++j)
            {
                Mat tmp_l()    
            }
        }
    }catch(cv::Exception& e)
    {
        cout << e << endl; 
    }
    return p_keys;
}
