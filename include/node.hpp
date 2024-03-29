//
// Created by Mpho Mbotho on 2021-08-13.
//

#pragma once

#include <list>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include <textbox.hpp>

namespace cyntactic {

    struct Node {
        using Ptr = std::unique_ptr<Node>;
        using GraphIt = std::pair<
                            std::list<Ptr>::const_iterator,
                            std::list<Ptr>::const_iterator>;

        typedef enum {
            INVALID,
            PROGRAM,
            IDENT,
            IMPORT,
            NUMBER_TYPE,
            LITERAL,
            BINARY_OP,
            BINARY_EXPR
        } Kind;

        Node() = default;
        Node(Kind kind) : Tag{kind} {}
        std::list<Ptr> Children;
        Kind   Tag{INVALID};
        std::string_view Source{};
        std::size_t Line{0};
        std::size_t Column{0};
        virtual std::string toString(bool compressed = true) const { return ""; }
    };
}


namespace cyntactic {

    template <>
    Node::GraphIt TreeGraph<Node>::countChildren() const;

    template <>
    bool TreeGraph<Node>::isOneliner() const;

    template <>
    const Node& TreeGraph<Node>::getNode(const Iterator& it) const;

    template <>
    std::string TreeGraph<Node>::createAtom() const;
}
