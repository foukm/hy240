# HY240 – Persistent Publish/Subscribe (2 Phases)

Implementation of a persistent publish/subscribe system in two phases:
- **Part 1 (Lists):** Sorted doubly linked lists per group.
- **Part 2 (BST):** Replaces the per-group list with a doubly linked Binary Search Tree (BST) and adds extra operations.

> Part 2 builds on the semantics of Part 1; only the core storage structure changes.


---

## 🧠 High-level Description

The system handles:
- **Groups** (streams/channels of information)
- **Info records** (messages/events per group)
- **Subscribers** and **Subscriptions** (which users follow which groups)

### Part 1 (Lists)
- Each group maintains a **sorted doubly linked list** of info records.
- Supported events include insert/publish, subscribe/unsubscribe, consume, print, etc.

### Part 2 (BST)
- The per-group list is replaced by a **doubly linked BST** (e.g., with inorder links).
- Adds/changes operations (e.g., faster search/delete, possible pruning controlled by parameters).
  
> The full assignment statements for both phases are included under [/docs](https://github.com/foukm/hy240/tree/main/docs)
---


