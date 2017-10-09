#include "message.h"

message::message()
{

}

message::message(std::string texte)
    : m_texte(texte)
{

}

std::string message::texte() const
{
    return m_texte;
}
