#include "linked_list.hpp"

#include <cassert>    // assert
#include <stdexcept>  // out_of_range

#include "private/internal.hpp"  // это не тот приват, о котором вы могли подумать

namespace itis {

    void LinkedList::Add(Element e) {
        // Tip 1: создайте узел в куче с переданным значением
        // Tip 2: есть 2 случая - список пустой и непустой
        // Tip 3: не забудьте обновить поля head и tail
        // напишите свой код здесь ...
        if (size_ == 0) {
            Node *node = new Node(e, nullptr);
            head_ = node;
            tail_ = node;
        }
        if (size_ != 0) {
            Node *prev_node = tail_;
            Node *node = new Node(e, nullptr);
            tail_ = node;
            prev_node->next = tail_;
        }
        size_++;
    }

    void LinkedList::Insert(int index, Element e) {
        internal::check_out_of_range(index, 0, size_ + 1);

        // Tip 1: вставка элементов на позицию size эквивалентно операции добавления в конец
        // Tip 2: рассмотрите несколько случаев:
        //        (1) список пустой,
        //        (2) добавляем в начало списка,
        //        (3) добавляем в конец списка
        //        (4) все остальное
        if(index == size_ || size_ == 0){
            Add(e);
            return;
        }
        if(index == 0){
            Node *node = new Node(e,head_);
            head_ = node;
            size_++;
            return;
        }
        if(size_ != 0){
            int counter = 0;
            for (Node *i = head_; i != nullptr ; i = i->next) {
                counter++;
                if(counter == index){
                    Node *prev_node = i;
                    Node *next_node = i->next;
                    Node *new_node = new Node(e,next_node);
                    prev_node->next = new_node;
                    size_++;
                    return;
                }
            }
        }
    }

    void LinkedList::Set(int index, Element e) {
        internal::check_out_of_range(index, 0, size_);
        // Tip 1: используйте функцию find_node(index)
        Node *found_node = find_node(index);
        found_node->data = e;
    }

    Element LinkedList::Remove(int index) {
        internal::check_out_of_range(index, 0, size_);
        // Tip 1: рассмотрите случай, когда удаляется элемент в начале списка
        // Tip 2: используйте функцию find_node(index)
        if(index == 0){
            Node *head = head_->next;
            Element e = head_->data;
            delete head_;
            head_ = head;
            size_--;
            return e;
        }
        Node *removed_node = find_node(index);
        Node *prev_node = find_node(index - 1);
        prev_node->next = removed_node->next;
        Element e = removed_node->data;
        delete removed_node;
        size_--;
        return e;
    }

    void LinkedList::Clear() {
        // Tip 1: люди в черном (MIB) пришли стереть вам память
        for (Node *node = head_; node != nullptr;) {
            Node *next_node = node->next;
            delete node;
            head_ = next_node;
            node = head_;
            size_--;
        }
        tail_ = nullptr;
    }

    Element LinkedList::Get(int index) const {
        internal::check_out_of_range(index, 0, size_);
        Node *found_node = find_node(index);
        return found_node->data;
    }

    int LinkedList::IndexOf(Element e) const {
        int counter = -1;
        for (Node *node = head_; node != nullptr; node = node->next){
            counter++;
            if(node->data == e){
                return counter;
            }
        }
        return kNotFoundElementIndex;
    }

    Node *LinkedList::find_node(int index) const {
        assert(index >= 0 && index < size_);
        // Tip 1: можете сразу обработать случаи поиска начала и конца списка
        if(index == 0){
            return head_;
        }
        if(index == size_ - 1){
            return tail_;
        }
        int counter = 0;
        for (Node *node = head_; node != nullptr; node = node->next) {
            counter++;
            if(counter == index){
                return node->next;
            }
        }
        return {};
    }

// РЕАЛИЗОВАНО

    LinkedList::~LinkedList() {
        Clear();
    }

    bool LinkedList::Contains(Element e) const {
        // если индекс не найден, значит и элемента нет
        return IndexOf(e) == kNotFoundElementIndex;
    }

    int LinkedList::GetSize() const {
        return size_;
    }

    bool LinkedList::IsEmpty() const {
        return size_ == 0;
    }

    Element LinkedList::tail() const {
        // вместо выброса ошибки в случае nullptr, римским парламентов было решено возвращать "специальное" значение
        return tail_ ? tail_->data : Element::UNINITIALIZED;
    }

    Element LinkedList::head() const {
        return head_ ? head_->data : Element::UNINITIALIZED;
    }

// === RESTRICTED AREA: необходимо для тестирования ===

    LinkedList::LinkedList(const std::vector<Element> &elements) {
        assert(!elements.empty());

        size_ = elements.size();
        head_ = new Node(elements[0], nullptr);

        auto current_node = head_;

        for (int index = 1; index < static_cast<int>(elements.size()); index++) {
            current_node->next = new Node(elements[index], nullptr);
            current_node = current_node->next;
        }
        tail_ = current_node;
    }

    std::ostream &operator<<(std::ostream &os, const LinkedList &list) {
        if (list.head_ != nullptr && list.tail_ != nullptr) {
            os << "{ ";
            for (auto current_node = list.head_; current_node != list.tail_; current_node = current_node->next) {
                os << internal::elem_to_str(current_node->data) << ", ";
            }
            os << internal::elem_to_str(list.tail_->data) << " }";
        } else {
            os << "{ nullptr }";
        }
        return os;
    }

    bool operator==(const LinkedList &list, const std::vector<Element> &elements) {
        if (list.size_ != static_cast<int>(elements.size())) return false;
        Node *current_node = list.head_;

        for (const auto e : elements) {
            if (current_node == nullptr) return false;
            if (current_node->data != e) return false;
            current_node = current_node->next;
        }
        return true;
    }

}  // namespace itis
