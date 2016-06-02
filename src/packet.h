#ifndef PACKET_H
#define PACKET_H
#include <string>

enum packetType {
        tileMine,
        tileChange,
        chat,
        playerPosition,
        players
};

/* class Packet { */
/*         public: */
/*                 packetType type; */
/*         private: */
/* }; */

std::string parsePacket(std::string &content, int pos)
{
        int len = content.length();
        int curPos = 0;
        int startPos = 0;
        for (int i = 0; i < len; i++) {
                bool last = (i == len - 1);
                if (content[i] == ',' || last) {
                        if (curPos == pos) {
                                return content.substr(startPos, i - startPos + (last ? 1 : 0));
                        }
                        curPos++;
                        startPos = i + 1;
                }
        }
        return "";
}

void splitPacket(std::string *&out, std::string &content)
{
        int pos = 0;
        int i = 0;
        while (pos != -1) {
                int lastPos = pos;
                pos = content.find(',', pos);
                if (pos == -1) {
                        out[i] = content.substr(lastPos, -1);
                        puts(out[i].c_str());
                        return;
                }
                out[i] = content.substr(lastPos, pos - lastPos);
                puts(out[i].c_str());
                i++;
                pos++;
        }
}

#endif
