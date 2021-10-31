#ifndef LZ77COMPRESSION_LZ77COMPRESSION_H
#define LZ77COMPRESSION_LZ77COMPRESSION_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class LZ77Compresion{
public:
    struct Node{
        int index;
        string data;
        Node *next;
    };

    void st_Node(Node *head, int index, string data){
        head->index = index;
        head->data = data;
        head->next = NULL;
    }

    void insert_Node(Node *head, int index, string data){
        Node *new_Node = new Node;
        new_Node->index = index;
        new_Node->data = data;
        new_Node->next = NULL;

        Node *curr = head;
        while (curr != NULL)
        {
            if (curr->next == NULL)
            {
                curr->next = new_Node;
                return;
            }
            curr = curr->next;
        }
    }

    Node *search_Node(Node *head, string data)
    {
        Node *curr = head;
        while (curr != NULL)
        {
            if (data.compare(curr->data) == 0)
                return curr;
            else
                curr = curr->next;
        }
        return NULL;
    }

    Node *search_Node(Node *head, int index)
    {
        Node *curr = head;
        while (curr != NULL)
        {
            if (index == curr->index)
                return curr;
            else
                curr = curr->next;
        }
        return NULL;
    }

    bool delete_Node(Node *head, Node *to_delete){
        if (to_delete == NULL)
            return false;
        else if (to_delete == head)
        {
            head = to_delete->next;
            delete to_delete;
            return true;
        }
        else{
            Node *curr = head;
            while (curr)
            {
                if (curr->next == to_delete)
                {
                    curr->next = to_delete->next;
                    delete to_delete;
                    return true;
                }
                curr = curr->next;
            }
            return false;
        }
    }

    vector <string> split(string str, char delimiter) {
        vector<string> internal;
        stringstream ss(str); // Turn the string into a stream.
        string tok;

        while (getline(ss, tok, delimiter)) {
            internal.push_back(tok);
        }

        return internal;
    }

    string LZ77(string input, int option)
    {
        string result;
        int length, char_info_selc = 0;

        if (option == 1)
        {
            int** result_ary = new int*[3];
            for (int i = 0; i < length; ++i)
                result_ary[i] = new int[length];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < length; j++)
                    result_ary[i][j] = 0;
            }

            int** char_info = new int*[3];
            for (int i = 0; i < length; ++i)
                char_info[i] = new int[length];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < length; j++)
                    char_info[i][j] = 0;
            }

            result_ary[0][0] = 0;
            result_ary[1][0] = 0;
            result_ary[2][0] = input[0];

            int result_count = 1;

            for (int i = 1; i < length; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (input[i] == input[j])
                    {
                        char_info[0][char_info_selc] = i - j;

                        char_info_selc++;
                    }

                }

                for (int j = 0; j < length; j++)
                {
                    if (char_info[0][j] != 0)
                    {
                        int start = i - char_info[0][j];

                        int count = 1;

                        for (int k = 0; k < length; k++)
                        {
                            if (input[start + count] == input[i + count])
                                count++;
                            else
                            {
                                char_info[1][j] = count;

                                if (i != (length - 1))
                                {
                                    if (char_info[0][j] + count == length)
                                        char_info[2][j] = 0;
                                    else
                                        char_info[2][j] = input[char_info[0][j] + count];
                                }
                                else
                                    char_info[2][j] = NULL;

                                break;
                            }
                        }
                    }
                }

                int large = 0;

                for (int k = 1; k < length; k++)
                {
                    if (char_info[1][large] == char_info[1][k])
                        large = k;
                    else if (char_info[1][large] < char_info[1][k])
                        large = k;
                }

                if (char_info[1][large] == 0)
                    char_info[2][large] = input[i];
                else
                {
                    i += char_info[1][large];
                    char_info[2][large] = input[i];
                }

                // Set final result info
                result_ary[0][result_count] = char_info[0][large];
                result_ary[1][result_count] = char_info[1][large];
                result_ary[2][result_count] = char_info[2][large];

                result_count++;

                for (int z = 0; z < 2; z++)
                {
                    for (int j = 0; j < length; j++)
                        char_info[z][j] = 0;
                }

                char_info_selc = 0;
            }

            for (int j = 0; j < length; j++)
            {
                if (result_ary[0][j] == 0 && result_ary[1][j] == 0)
                {
                    if (result_ary[2][j] != NULL || result_ary[2][j] != 0)
                    {
                        char z = result_ary[2][j];
                        result += to_string(result_ary[0][j]) + "," + to_string(result_ary[1][j]) + "," + z + " ";
                    }
                }
                else
                {
                    char z = result_ary[2][j];
                    result += to_string(result_ary[0][j]) + "," + to_string(result_ary[1][j]) + "," + z + " ";
                }
            }

            return result;
        }
        else if (option == 2)
        {
            vector<string> s_input = split(input, ' ');

            for (int i = 0; i < s_input.size(); ++i)
            {
                vector<string> ss_input = split(s_input[i], ',');

                int p = stoi(ss_input[0]),
                        l = stoi(ss_input[1]);
                string ch;
                if (ss_input[2][0] == '0')
                    ch = ' ';
                else
                    ch = ss_input[2];

                if (p != 0)
                {
                    int result_len = (int)result.length();
                    for (int x = 0; x < l; x++)
                        result += result[result_len - p + x];
                }

                if (ch[0] != '0' || ch[0] != NULL)
                    result += ch;
            }
            return result;
        }
    }

    // Codigo fuente: https://gist.github.com/MajedSiefALnasr/32cff52b01d764ee158f2c36e4e84d95
    // Se puede visitar el perfil del creador en: https://gist.github.com/MajedSiefALnasr
};

#endif //LZ77COMPRESSION_LZ77COMPRESSION_H
