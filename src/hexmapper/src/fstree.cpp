#include "fstree.h"

FsNode ParseDirectory(const char* basePathStr) {
    using namespace std;
    namespace fs = std::filesystem;

    size_t MAX_ENTRY_COUNT = 10000;

    FsNode root = {};
    root.path = std::string(basePathStr);
    root.dirs.reserve(MAX_ENTRY_COUNT);
    root.files.reserve(MAX_ENTRY_COUNT);
    root.isDirectory = true;

    vector<FsNode*> allNodes;

    unordered_set<std::string> visited;
    vector<FsNode*> nodes;
    nodes.push_back(&root);
    while (!nodes.empty()) {
        FsNode* node = nodes.back();
        nodes.pop_back();

        TraceLog(LOG_INFO, "Found path: %s", node->path.c_str());
        fs::path path = node->path;
        for (const auto& entry : fs::directory_iterator(path)) {
            FsNode newNode = {};
            newNode.path = entry.path();
            newNode.files.reserve(MAX_ENTRY_COUNT);
            newNode.dirs.reserve(MAX_ENTRY_COUNT);
            if (entry.is_regular_file()) {
                newNode.isDirectory = false;
                if (node->files.size() == MAX_ENTRY_COUNT) {
                    TraceLog(LOG_ERROR,
                             "Maximum number of files exceeded for "
                             "%s. The allowed number is %d. Some files will "
                             "not be processed.",
                             node->path.c_str(), MAX_ENTRY_COUNT);
                    break;
                }
                node->files.push_back(move(newNode));
                allNodes.push_back(&node->files.back());
            } else if (entry.is_directory()) {
                newNode.isDirectory = true;
                if (node->dirs.size() == MAX_ENTRY_COUNT) {
                    TraceLog(LOG_ERROR,
                             "Maximum number of subdirectories exceeded for "
                             "%s. The allowed number is %d. Some files will "
                             "not be processed.",
                             node->path.c_str(), MAX_ENTRY_COUNT);
                    break;
                }
                node->dirs.push_back(move(newNode));
                FsNode* newNodePtr = &node->dirs.back();
                allNodes.push_back(newNodePtr);
                if (visited.find(newNode.path) == visited.end()) {
                    nodes.push_back(newNodePtr);
                }
            }
        }

        visited.insert(node->path);
    }

    for(FsNode* node : allNodes) {
        node->files.shrink_to_fit();
        node->dirs.shrink_to_fit();
    }

    return root;
}
