// Use a prefix array of products. Whenever the product array is reset, add a sentinel element '1'.

class ProductOfNumbers {
public:
    ProductOfNumbers() {
        prod = {1};
    }
    
    void add(int num) {
        if (num == 0) prod = {1};
        else prod.push_back(prod.back() * num);
    } 
    
    int getProduct(int k) {
        if (k >= prod.size()) return 0;
        return prod.back() / prod[prod.size()-1-k];        
    }
private:
    vector<int> prod;
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
