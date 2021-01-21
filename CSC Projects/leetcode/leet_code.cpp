/*These are examples of coding solutions found on leetcode.com This will be updated as progress is continued. 
Linked Lists
Project: Add Two Numbers 
Project: Reverse Linked List


//Arrays and strings
Project: Two Sum
Project: is palindrome
Project: Reverse String
Project: Reverse words in a string
Project: Reverse Words in a String II
*/



//Linked Lists:

  
//Project: Add Two Numbers
// Add Two Numbers from two linked lists. These digits are stored reverse order.
// List : 3->2->1  =123 


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

//    Node* new_node = new Node();  

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode *current_l1 = nullptr;
        ListNode *current_l2 = nullptr;
        ListNode *current_l3 = nullptr;
        ListNode *l3=new ListNode();
        
        ListNode *temp=nullptr;
        int temp_Num;
        current_l1=l1;
        current_l2=l2;
        current_l3=l3;
        int num1=0;
        int num2=0;
        
        int remainder=0;
        
        while(current_l1!=nullptr || current_l2!=nullptr)
        {
            if(current_l1==nullptr)
            {
                if(remainder==1)
                {
                    temp_Num=current_l2->val+1;
                    if(temp_Num>9)
                    {
                        remainder=1;
                        temp_Num=temp_Num-10;
                        
                    }
                    else
                    {
                        remainder=0;
                    }
                    
                    
                }
                //remainder==0
                else if(remainder==0)
                {
                    temp_Num=current_l2->val;
                }
                current_l2=current_l2->next;
                current_l3->val=temp_Num;
                
               

            }
            
            
            //l2 is nullptr
            else if(current_l2==nullptr)
            {
                if(remainder==1)
                {
                    temp_Num=current_l1->val+1;
                    if(temp_Num>9)
                    {
                        remainder=1;
                        temp_Num=temp_Num-10;
                    }
                    else if(temp_Num<=9)
                    {
                        remainder=0;
                        
                    }
                    
                }
                //remainder==0
                else
                {
                    temp_Num=current_l1->val;
                }
                current_l1=current_l1->next;
                current_l3->val=temp_Num;
                

            }
            
            // Both lists are fine both not at the end.
            else
            {
                num1=current_l1->val;
                num2=current_l2->val;
                if(remainder==0)
                {
                temp_Num=num1+num2;
                }
                else if(remainder==1)
                {
                    temp_Num=num1+num2+remainder;
                    remainder=0;
                }
                if(temp_Num>9)
                {
                    remainder=1;
                    temp_Num=temp_Num-10;
                }
                
                current_l3->val=temp_Num;
                current_l2=current_l2->next;
                current_l1=current_l1->next;
                
            }
            
            
            
            if((current_l1!=nullptr && current_l2!=nullptr)||(current_l1!=nullptr && current_l2==nullptr)||(current_l2!=nullptr && current_l1==nullptr))
            {
            ListNode *temp=new ListNode();
            current_l3->next=temp;
            current_l3=current_l3->next;
            }
         //add
               
           
        }
        
        if(remainder==1)
        {
            ListNode *temp = new ListNode();
            current_l3->next=temp;
            current_l3=current_l3->next;
            current_l3->val=1;
        }
        
        return l3;
        
        
    }
};



//Project :   Reverse Linked List

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) 
    {
        ListNode* current=nullptr;

        ListNode* temp=nullptr;
        ListNode* prev=nullptr;
        current=head;
        while(current!=nullptr)
        {
           temp=current->next;
            current->next=prev;
            prev=current;
            current=temp;
           
            
        }
        head=prev;
        return head;
      
    }
};


//Project: Two Sum
/*Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    
    {
        int sum;
        vector <int> res;
        int num1, num2;
        int count=0;
        int size=nums.size();
        int end=size-1;
        for(int i=0;i<size-1;i++)
        {
            for(int j=1;j<size;j++)
            {
                if(i!=j)
                {
                    num1=nums[i];
                    num2=nums[j];
                    sum=num1+num2;
                    if(sum==target)
                    {
                        res.push_back(i);
                        res.push_back(j);
                        return res;
                    }
                }
            }
         
                     
            
    
        }
        return res;
    }     
    
};

//Project: Is Palindrome
//Determine if string is a palindrome

class Solution {
public:
    //remove everything except letters
    //reverse check if they are equal.
    bool isPalindrome(string s) 
    {
        //isalpha(str[i])
        vector<char>letters;
        vector<char>backwards;
        
        int size=s.size();
        for(int i=0;i<size;i++)
        {
            if(isalpha(s[i])||isdigit(s[i]))
            {
                letters.push_back(tolower(s[i]));
            }
        }
        
           for (int j = letters.size() - 1; j >= 0; j--)
    {

        backwards.push_back(letters[j]);
    }
        
        if(backwards==letters)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
};

//Project: Reverse String
class Solution {
public:
    void reverseString(vector<char>& s) 
    {
        reverse(s.begin(),s.end());
    }
};


//Project:   Reverse Words in a String
//

class Solution {
public:
    string reverseWords(string s) 
    {
        
    int size = s.length();
    stack<string>rev;
    string word;
    
    
    for (int i = 0; i < size; i++)
    {
        if (!iswspace(s[i]))
        {
            
            word.push_back(s[i]);
        }
        else
        {
            if (word.length() > 0)
            {
                rev.push(word);
                word = "";
            }
        }
    }
    if (word.length() > 0)
    {
        rev.push(word);
        word = "";
    }

    while (!rev.empty())
    {
        word.append(rev.top());
        rev.pop();
        if(!rev.empty())
        {
        word.append(" ");
        }
    }
        return word;
    }
};

// Project: Reverse Words in a String II
class Solution {
public:
    void reverseWords(vector<char>& s) 
    {
        int size = s.size();
    int count = 0;
    reverse(s.begin(), s.end());

    for (int i = 0; i < size; i++)
    {

        if (iswspace(s[i]))
        {
            reverse(s.begin() + (i - count), s.begin() + (i));
            count = 0;
            
        }  
        else
        count++;

    }
    reverse(s.end() - count, s.end());
        
    }
};

