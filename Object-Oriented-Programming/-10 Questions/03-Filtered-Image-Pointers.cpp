/*
==========================================
FILTERED IMAGE USING POINTERS QUESTION
==========================================

PROBLEM STATEMENT:
------------------
Create a comprehensive Image Processing System using pointers with the following requirements:

1. Image Class: (width, height, pixel data using pointers)
2. Filter Classes:
   - GrayscaleFilter
   - BlurFilter
   - EdgeDetectionFilter
   - BrightnessFilter
   - ContrastFilter
3. Pixel Class: (red, green, blue, alpha)
4. Features:
   - Load/Save images
   - Apply various filters
   - Memory management using pointers
   - Pointer arithmetic for pixel manipulation
   - Multiple filter combinations
   - Image statistics calculation

IMPLEMENTATION REQUIREMENTS:
- Use dynamic memory allocation with pointers
- Implement pointer arithmetic for pixel access
- Use smart pointers for memory management
- Implement filter inheritance hierarchy
- Use templates for generic operations
- Handle memory leaks and exceptions
- Optimize performance with pointer operations
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
using namespace std;

// ==========================================
// EXCEPTION CLASSES
// ==========================================

class ImageException : public exception {
private:
    string message;
public:
    ImageException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class FilterException : public exception {
private:
    string message;
public:
    FilterException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ==========================================
// PIXEL CLASS
// ==========================================

class Pixel {
private:
    unsigned char red, green, blue, alpha;

public:
    Pixel(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255)
        : red(r), green(g), blue(b), alpha(a) {}

    // Getters
    unsigned char getRed() const { return red; }
    unsigned char getGreen() const { return green; }
    unsigned char getBlue() const { return blue; }
    unsigned char getAlpha() const { return alpha; }

    // Setters
    void setRed(unsigned char r) { red = r; }
    void setGreen(unsigned char g) { green = g; }
    void setBlue(unsigned char b) { blue = b; }
    void setAlpha(unsigned char a) { alpha = a; }

    // Set all components
    void setRGB(unsigned char r, unsigned char g, unsigned char b) {
        red = r; green = g; blue = b;
    }

    // Get grayscale value
    unsigned char getGrayscale() const {
        return static_cast<unsigned char>(0.299 * red + 0.587 * green + 0.114 * blue);
    }

    // Set grayscale
    void setGrayscale(unsigned char gray) {
        red = green = blue = gray;
    }

    // Operator overloading for pixel operations
    Pixel operator+(const Pixel& other) const {
        return Pixel(
            min(255, red + other.red),
            min(255, green + other.green),
            min(255, blue + other.blue),
            alpha
        );
    }

    Pixel operator-(const Pixel& other) const {
        return Pixel(
            max(0, red - other.red),
            max(0, green - other.green),
            max(0, blue - other.blue),
            alpha
        );
    }

    Pixel operator*(double factor) const {
        return Pixel(
            static_cast<unsigned char>(min(255.0, red * factor)),
            static_cast<unsigned char>(min(255.0, green * factor)),
            static_cast<unsigned char>(min(255.0, blue * factor)),
            alpha
        );
    }

    bool operator==(const Pixel& other) const {
        return red == other.red && green == other.green && 
               blue == other.blue && alpha == other.alpha;
    }

    // Friend function for output
    friend ostream& operator<<(ostream& os, const Pixel& pixel);
};

ostream& operator<<(ostream& os, const Pixel& pixel) {
    os << "RGB(" << (int)pixel.red << "," << (int)pixel.green << "," << (int)pixel.blue << ")";
    return os;
}

// ==========================================
// BASE FILTER CLASS
// ==========================================

class Filter {
protected:
    string filterName;
    static int filterCounter;

public:
    Filter(string name) : filterName(name) {
        filterCounter++;
    }

    virtual ~Filter() {
        filterCounter--;
    }

    // Pure virtual function - must be implemented by derived classes
    virtual void apply(Pixel** image, int width, int height) = 0;

    // Virtual function with default implementation
    virtual string getFilterName() const {
        return filterName;
    }

    static int getFilterCounter() { return filterCounter; }
};

int Filter::filterCounter = 0;

// ==========================================
// GRAYSCALE FILTER
// ==========================================

class GrayscaleFilter : public Filter {
public:
    GrayscaleFilter() : Filter("Grayscale") {}

    void apply(Pixel** image, int width, int height) override {
        cout << "Applying " << filterName << " filter..." << endl;
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned char gray = image[y][x].getGrayscale();
                image[y][x].setGrayscale(gray);
            }
        }
    }
};

// ==========================================
// BLUR FILTER
// ==========================================

class BlurFilter : public Filter {
private:
    int blurRadius;

public:
    BlurFilter(int radius = 1) : Filter("Blur"), blurRadius(radius) {}

    void apply(Pixel** image, int width, int height) override {
        cout << "Applying " << filterName << " filter with radius " << blurRadius << "..." << endl;
        
        // Create a copy of the image for blurring
        Pixel** tempImage = new Pixel*[height];
        for (int i = 0; i < height; i++) {
            tempImage[i] = new Pixel[width];
            for (int j = 0; j < width; j++) {
                tempImage[i][j] = image[i][j];
            }
        }

        // Apply blur using convolution
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int totalR = 0, totalG = 0, totalB = 0;
                int count = 0;

                // Calculate average of surrounding pixels
                for (int dy = -blurRadius; dy <= blurRadius; dy++) {
                    for (int dx = -blurRadius; dx <= blurRadius; dx++) {
                        int ny = y + dy;
                        int nx = x + dx;
                        
                        if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                            totalR += tempImage[ny][nx].getRed();
                            totalG += tempImage[ny][nx].getGreen();
                            totalB += tempImage[ny][nx].getBlue();
                            count++;
                        }
                    }
                }

                // Set the blurred pixel
                if (count > 0) {
                    image[y][x].setRGB(
                        totalR / count,
                        totalG / count,
                        totalB / count
                    );
                }
            }
        }

        // Clean up temporary image
        for (int i = 0; i < height; i++) {
            delete[] tempImage[i];
        }
        delete[] tempImage;
    }
};

// ==========================================
// EDGE DETECTION FILTER
// ==========================================

class EdgeDetectionFilter : public Filter {
public:
    EdgeDetectionFilter() : Filter("Edge Detection") {}

    void apply(Pixel** image, int width, int height) override {
        cout << "Applying " << filterName << " filter..." << endl;
        
        // Sobel operators
        int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
        int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

        // Create a copy of the image
        Pixel** tempImage = new Pixel*[height];
        for (int i = 0; i < height; i++) {
            tempImage[i] = new Pixel[width];
            for (int j = 0; j < width; j++) {
                tempImage[i][j] = image[i][j];
            }
        }

        // Apply edge detection
        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                int gx = 0, gy = 0;

                // Apply Sobel operators
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        unsigned char gray = tempImage[y + dy][x + dx].getGrayscale();
                        gx += gray * sobelX[dy + 1][dx + 1];
                        gy += gray * sobelY[dy + 1][dx + 1];
                    }
                }

                // Calculate magnitude
                int magnitude = static_cast<int>(sqrt(gx * gx + gy * gy));
                magnitude = min(255, magnitude);

                // Set edge pixel
                image[y][x].setGrayscale(static_cast<unsigned char>(magnitude));
            }
        }

        // Clean up temporary image
        for (int i = 0; i < height; i++) {
            delete[] tempImage[i];
        }
        delete[] tempImage;
    }
};

// ==========================================
// BRIGHTNESS FILTER
// ==========================================

class BrightnessFilter : public Filter {
private:
    int brightnessAdjustment;

public:
    BrightnessFilter(int adjustment = 50) : Filter("Brightness"), brightnessAdjustment(adjustment) {}

    void apply(Pixel** image, int width, int height) override {
        cout << "Applying " << filterName << " filter with adjustment " << brightnessAdjustment << "..." << endl;
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int newR = min(255, max(0, image[y][x].getRed() + brightnessAdjustment));
                int newG = min(255, max(0, image[y][x].getGreen() + brightnessAdjustment));
                int newB = min(255, max(0, image[y][x].getBlue() + brightnessAdjustment));
                
                image[y][x].setRGB(
                    static_cast<unsigned char>(newR),
                    static_cast<unsigned char>(newG),
                    static_cast<unsigned char>(newB)
                );
            }
        }
    }
};

// ==========================================
// CONTRAST FILTER
// ==========================================

class ContrastFilter : public Filter {
private:
    double contrastFactor;

public:
    ContrastFilter(double factor = 1.5) : Filter("Contrast"), contrastFactor(factor) {}

    void apply(Pixel** image, int width, int height) override {
        cout << "Applying " << filterName << " filter with factor " << contrastFactor << "..." << endl;
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int newR = static_cast<int>((image[y][x].getRed() - 128) * contrastFactor + 128);
                int newG = static_cast<int>((image[y][x].getGreen() - 128) * contrastFactor + 128);
                int newB = static_cast<int>((image[y][x].getBlue() - 128) * contrastFactor + 128);
                
                image[y][x].setRGB(
                    static_cast<unsigned char>(min(255, max(0, newR))),
                    static_cast<unsigned char>(min(255, max(0, newG))),
                    static_cast<unsigned char>(min(255, max(0, newB)))
                );
            }
        }
    }
};

// ==========================================
// IMAGE CLASS
// ==========================================

class Image {
private:
    int width, height;
    Pixel** pixelData;
    string imageName;
    static int imageCounter;

public:
    Image(int w, int h, string name = "Image") : width(w), height(h), imageName(name) {
        if (width <= 0 || height <= 0) {
            throw ImageException("Invalid image dimensions");
        }

        imageCounter++;
        
        // Allocate memory for pixel data using pointers
        pixelData = new Pixel*[height];
        for (int i = 0; i < height; i++) {
            pixelData[i] = new Pixel[width];
        }

        // Initialize with default pixels
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixelData[y][x] = Pixel(255, 255, 255); // White pixels
            }
        }
    }

    // Copy constructor with deep copy
    Image(const Image& other) : width(other.width), height(other.height), imageName(other.imageName) {
        imageCounter++;
        
        pixelData = new Pixel*[height];
        for (int i = 0; i < height; i++) {
            pixelData[i] = new Pixel[width];
            for (int j = 0; j < width; j++) {
                pixelData[i][j] = other.pixelData[i][j];
            }
        }
    }

    // Destructor - clean up memory
    ~Image() {
        imageCounter--;
        if (pixelData != nullptr) {
            for (int i = 0; i < height; i++) {
                delete[] pixelData[i];
            }
            delete[] pixelData;
        }
    }

    // Assignment operator with deep copy
    Image& operator=(const Image& other) {
        if (this != &other) {
            // Clean up existing memory
            if (pixelData != nullptr) {
                for (int i = 0; i < height; i++) {
                    delete[] pixelData[i];
                }
                delete[] pixelData;
            }

            // Copy data
            width = other.width;
            height = other.height;
            imageName = other.imageName;

            // Allocate new memory
            pixelData = new Pixel*[height];
            for (int i = 0; i < height; i++) {
                pixelData[i] = new Pixel[width];
                for (int j = 0; j < width; j++) {
                    pixelData[i][j] = other.pixelData[i][j];
                }
            }
        }
        return *this;
    }

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    string getName() const { return imageName; }
    Pixel** getPixelData() { return pixelData; }

    // Set pixel using pointer arithmetic
    void setPixel(int x, int y, const Pixel& pixel) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixelData[y][x] = pixel;
        } else {
            throw ImageException("Pixel coordinates out of bounds");
        }
    }

    // Get pixel using pointer arithmetic
    Pixel getPixel(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return pixelData[y][x];
        } else {
            throw ImageException("Pixel coordinates out of bounds");
        }
    }

    // Create a test pattern
    void createTestPattern() {
        cout << "Creating test pattern..." << endl;
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned char r = static_cast<unsigned char>((x * 255) / width);
                unsigned char g = static_cast<unsigned char>((y * 255) / height);
                unsigned char b = static_cast<unsigned char>((x + y) * 255 / (width + height));
                
                pixelData[y][x].setRGB(r, g, b);
            }
        }
    }

    // Apply filter
    void applyFilter(Filter& filter) {
        try {
            filter.apply(pixelData, width, height);
        } catch (const exception& e) {
            cout << "Error applying filter: " << e.what() << endl;
        }
    }

    // Calculate image statistics
    void calculateStatistics() {
        cout << "\nImage Statistics for " << imageName << ":" << endl;
        cout << "=================================" << endl;
        cout << "Dimensions: " << width << "x" << height << endl;
        cout << "Total Pixels: " << width * height << endl;

        int totalR = 0, totalG = 0, totalB = 0;
        int minR = 255, minG = 255, minB = 255;
        int maxR = 0, maxG = 0, maxB = 0;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                totalR += pixelData[y][x].getRed();
                totalG += pixelData[y][x].getGreen();
                totalB += pixelData[y][x].getBlue();

                minR = min(minR, (int)pixelData[y][x].getRed());
                minG = min(minG, (int)pixelData[y][x].getGreen());
                minB = min(minB, (int)pixelData[y][x].getBlue());

                maxR = max(maxR, (int)pixelData[y][x].getRed());
                maxG = max(maxG, (int)pixelData[y][x].getGreen());
                maxB = max(maxB, (int)pixelData[y][x].getBlue());
            }
        }

        int totalPixels = width * height;
        cout << "Average RGB: (" << totalR / totalPixels << ", " 
             << totalG / totalPixels << ", " << totalB / totalPixels << ")" << endl;
        cout << "Min RGB: (" << minR << ", " << minG << ", " << minB << ")" << endl;
        cout << "Max RGB: (" << maxR << ", " << maxG << ", " << maxB << ")" << endl;
    }

    // Display image information
    void display() const {
        cout << "Image: " << imageName << endl;
        cout << "Dimensions: " << width << "x" << height << endl;
        cout << "Sample pixels:" << endl;
        
        // Display a few sample pixels
        for (int y = 0; y < min(3, height); y++) {
            for (int x = 0; x < min(3, width); x++) {
                cout << "Pixel(" << x << "," << y << "): " << pixelData[y][x] << endl;
            }
        }
    }

    // Static function
    static int getImageCounter() { return imageCounter; }

    // Operator overloading
    bool operator==(const Image& other) const {
        if (width != other.width || height != other.height) return false;
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (pixelData[y][x] != other.pixelData[y][x]) return false;
            }
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const Image& image);
};

int Image::imageCounter = 0;

ostream& operator<<(ostream& os, const Image& image) {
    os << "Image: " << image.imageName << " (" << image.width << "x" << image.height << ")";
    return os;
}

// ==========================================
// TEMPLATE CLASS FOR IMAGE OPERATIONS
// ==========================================

template<typename T>
class ImageProcessor {
private:
    vector<shared_ptr<T>> items;

public:
    void addItem(shared_ptr<T> item) {
        items.push_back(item);
    }

    void removeItem(shared_ptr<T> item) {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        }
    }

    void processAll() {
        for (auto& item : items) {
            item->display();
        }
    }

    int getCount() const { return items.size(); }
};

// ==========================================
// IMAGE PROCESSING SYSTEM CLASS
// ==========================================

class ImageProcessingSystem {
private:
    vector<shared_ptr<Image>> images;
    vector<shared_ptr<Filter>> filters;
    string outputDirectory;

public:
    ImageProcessingSystem(string outputDir = "./output/") : outputDirectory(outputDir) {}

    ~ImageProcessingSystem() {
        cout << "Image Processing System shutting down..." << endl;
    }

    // Create image
    void createImage(int width, int height, string name) {
        try {
            auto image = make_shared<Image>(width, height, name);
            images.push_back(image);
            cout << "Image '" << name << "' created successfully!" << endl;
        } catch (const exception& e) {
            cout << "Error creating image: " << e.what() << endl;
        }
    }

    // Add filter
    void addFilter(shared_ptr<Filter> filter) {
        filters.push_back(filter);
        cout << "Filter '" << filter->getFilterName() << "' added successfully!" << endl;
    }

    // Apply filter to image
    void applyFilterToImage(string imageName, string filterName) {
        try {
            shared_ptr<Image> targetImage = nullptr;
            shared_ptr<Filter> targetFilter = nullptr;

            // Find image
            for (auto& image : images) {
                if (image->getName() == imageName) {
                    targetImage = image;
                    break;
                }
            }

            // Find filter
            for (auto& filter : filters) {
                if (filter->getFilterName() == filterName) {
                    targetFilter = filter;
                    break;
                }
            }

            if (!targetImage) {
                throw ImageException("Image not found: " + imageName);
            }
            if (!targetFilter) {
                throw FilterException("Filter not found: " + filterName);
            }

            targetImage->applyFilter(*targetFilter);
            cout << "Filter '" << filterName << "' applied to image '" << imageName << "'" << endl;
        } catch (const exception& e) {
            cout << "Error applying filter: " << e.what() << endl;
        }
    }

    // Generate test images and apply filters
    void generateTestImages() {
        cout << "\nGenerating test images..." << endl;

        // Create test images
        createImage(100, 100, "TestImage1");
        createImage(200, 150, "TestImage2");
        createImage(150, 200, "TestImage3");

        // Create test patterns
        for (auto& image : images) {
            image->createTestPattern();
        }

        // Add filters
        addFilter(make_shared<GrayscaleFilter>());
        addFilter(make_shared<BlurFilter>(2));
        addFilter(make_shared<EdgeDetectionFilter>());
        addFilter(make_shared<BrightnessFilter>(30));
        addFilter(make_shared<ContrastFilter>(1.8));

        cout << "Test images generated successfully!" << endl;
    }

    // Process all images with all filters
    void processAllImages() {
        cout << "\nProcessing all images with all filters..." << endl;

        for (auto& image : images) {
            cout << "\nProcessing image: " << image->getName() << endl;
            cout << "=================================" << endl;

            // Display original statistics
            image->calculateStatistics();

            // Apply each filter
            for (auto& filter : filters) {
                cout << "\nApplying " << filter->getFilterName() << "..." << endl;
                image->applyFilter(*filter);
                image->calculateStatistics();
            }
        }
    }

    // Generate system report
    void generateReport() {
        cout << "\n=== IMAGE PROCESSING SYSTEM REPORT ===" << endl;
        cout << "Total Images: " << Image::getImageCounter() << endl;
        cout << "Total Filters: " << Filter::getFilterCounter() << endl;
        
        cout << "\nImages in system:" << endl;
        for (auto& image : images) {
            image->display();
            cout << "------------------------" << endl;
        }

        cout << "\nFilters in system:" << endl;
        for (auto& filter : filters) {
            cout << "- " << filter->getFilterName() << endl;
        }
    }
};

// ==========================================
// DEMONSTRATION FUNCTION
// ==========================================

void demonstrateImageProcessing() {
    cout << "IMAGE PROCESSING SYSTEM DEMONSTRATION" << endl;
    cout << "=====================================" << endl;

    ImageProcessingSystem ips;

    // Generate test images and filters
    ips.generateTestImages();

    // Process images
    ips.processAllImages();

    // Generate report
    ips.generateReport();

    // Demonstrate specific filter applications
    cout << "\n=== SPECIFIC FILTER DEMONSTRATIONS ===" << endl;
    
    ips.applyFilterToImage("TestImage1", "Grayscale");
    ips.applyFilterToImage("TestImage2", "Blur");
    ips.applyFilterToImage("TestImage3", "Edge Detection");
}

// ==========================================
// TRICKY DRY RUN PROBLEMS
// ==========================================

/*
Problem 1: What will be the output?
class Pixel {
    int r, g, b;
public:
    Pixel(int x = 0) : r(x), g(x), b(x) {}
    Pixel operator+(const Pixel& p) {
        return Pixel(r + p.r + 1);
    }
    friend ostream& operator<<(ostream& os, const Pixel& p) {
        return os << "(" << p.r << "," << p.g << "," << p.b << ")";
    }
};
int main() {
    Pixel p1(10), p2(20);
    cout << p1 + p2;
    return 0;
}
Answer: (31,31,31)

Problem 2: What will be the output?
class Image {
    static int count;
    int* data;
public:
    Image() { 
        count++; 
        data = new int[count];
        cout << "Image" << count; 
    }
    ~Image() { 
        delete[] data; 
        cout << "~Image" << count; 
    }
};
int Image::count = 0;
int main() {
    Image img1, img2;
    { Image img3; }
    return 0;
}
Answer: Image1Image2Image3~Image3~Image2~Image1

Problem 3: What will be the output?
class Filter {
    int strength;
public:
    Filter(int s = 1) : strength(s) {}
    virtual void apply() { cout << "Base" << strength; }
};
class BlurFilter : public Filter {
public:
    BlurFilter(int s) : Filter(s + 1) {}
    void apply() override { cout << "Blur" << strength; }
};
int main() {
    Filter* f = new BlurFilter(5);
    f->apply();
    delete f;
    return 0;
}
Answer: Blur6
*/

int main() {
    demonstrateImageProcessing();
    return 0;
} 