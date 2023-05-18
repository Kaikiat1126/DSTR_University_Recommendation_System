#pragma once
#include "Structure.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class FeedbackList {
    FeedbackNode* head;
    FeedbackNode* tail;
    FeedbackNode* current;
    int sizeOfLinkedList;

public:
    FeedbackList();
    ~FeedbackList();
    void InsertToFrontOfList(FeedbackNode* node);
    FeedbackNode* getLatestFeedback();
    FeedbackNode* getPrevFeedback();
    FeedbackNode* getNextFeedback();
    int capacity() const;
    void replyFeedback(string reply, string userID);
    void display();
    void displayCurrent();
    FeedbackNode* getCurrentFeedback();

    FeedbackNode* isReplyTo(FeedbackNode* node);

private:
    void destroy(FeedbackNode* node);
};

FeedbackList::FeedbackList() : head(nullptr), tail(nullptr), current(nullptr), sizeOfLinkedList(0) {}

FeedbackList::~FeedbackList() {
    destroy(head);
}

FeedbackNode* FeedbackList::isReplyTo(FeedbackNode* node) {
    FeedbackNode* ptr = tail;

    while (ptr) {
        if (ptr->feedback.FeedbackID == node->feedback.ReplyTo) {
            return ptr;
        }
        ptr = ptr->PrevAddress;
    }
    return nullptr;
}

void FeedbackList::InsertToFrontOfList(FeedbackNode* node) {
    if (!head) {
        head = tail = node;
        ++sizeOfLinkedList;
        return;
    }
    if (node->feedback.ReplyTo == -1) {
        node->NextAddress = head;
        head->PrevAddress = node;
        head = node;
    }
    else {
        FeedbackNode* parent = isReplyTo(node);
        if (parent) {
            node->ChildAddress = parent->ChildAddress;
            parent->ChildAddress = node;
        }
    }

    ++sizeOfLinkedList;
}

FeedbackNode* FeedbackList::getLatestFeedback() {
    current = head;
    return current;
}

FeedbackNode* FeedbackList::getPrevFeedback() {
    if (!current || !current->PrevAddress) {
        Message::warning("Feedback has reached the top");
        return current;
    }
    current = current->PrevAddress;
    return current;
}

FeedbackNode* FeedbackList::getNextFeedback() {
    if (!current || !current->NextAddress) {
        Message::warning("Feedback has reached the bottom");
        return current;
    }
    current = current->NextAddress;
    return current;
}

void FeedbackList::replyFeedback(string reply, string userName) {
    time_t now = time(0);
    auto* newNode = new FeedbackNode;

    newNode->feedback.FeedbackID = now;
    newNode->feedback.UserName = userName;
    newNode->feedback.Content = reply;
    if (current)
        newNode->feedback.ReplyTo = current->feedback.FeedbackID;

    InsertToFrontOfList(newNode);
}

void FeedbackList::destroy(FeedbackNode* node) {
    if (node) {
        destroy(node->NextAddress);
        delete node;
    }
}

int FeedbackList::capacity() const {
    return sizeOfLinkedList;
}

void FeedbackList::display() {
    FeedbackNode* node = tail;
    FeedbackNode* child = nullptr;

    cout << left << setw(15) << "FeedbackID" << setw(15) << "UserName"
         << setw(15) << "ReplyTo" << setw(25) << "Content" << "Institution" << endl;

    while (node) {
        cout << setw(15) << node->feedback.FeedbackID << setw(15) << node->feedback.UserName
            << setw(15) << node->feedback.ReplyTo << setw(25) << node->feedback.Content << node->feedback.Institution << endl;
        child = node->ChildAddress;
        while (child) {
            cout << " ©¸©¤©¤ " << left << setw(15) << child->feedback.FeedbackID << setw(15) << child->feedback.UserName
                << setw(15) << child->feedback.ReplyTo << setw(25) << child->feedback.Content << child->feedback.Institution << endl;
            child = child->ChildAddress;
        }
        cout << endl;
        node = node->PrevAddress;
    }
}

void FeedbackList::displayCurrent() {
    if (!current)
        return;

    FeedbackNode* node = current;
    FeedbackNode* child = nullptr;
    
    time_t time = node->feedback.FeedbackID;
    char dt[26];

    ctime_s(dt, sizeof(dt), &time);

    cout << left << setw(15) << "UserName" << setw(50) << "Content" << "Date Time" << endl;
         
    cout << left << setw(15) << node->feedback.UserName << setw(50) << node->feedback.Content << dt << endl;
    child = node->ChildAddress;
    while (child) {
        time = child->feedback.FeedbackID;
        ctime_s(dt, sizeof(dt), &time);
        cout << left << " ©¸©¤©¤ " << setw(15) << child->feedback.UserName << setw(50)
            << child->feedback.Content << dt << endl;
        child = child->ChildAddress;
    }
    node = node->PrevAddress;
}

FeedbackNode* FeedbackList::getCurrentFeedback()
{
    return current;
}
