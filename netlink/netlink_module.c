#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/init.h>
#include <net/sock.h>

#define NETLINK_TEST 17

static struct sock *nl_sock;
char *msg="kernel message";

static void nl_recv_msg (struct sk_buff *skb_in) {
    struct nlmsghdr *nlh;
    struct sk_buff *skb_out;
    int msg_size,pid;

    // receiving from user process
    nlh = (struct nlmsghdr *)skb_in->data;
    pid = nlh->nlmsg_pid;
    printk(KERN_INFO "received netlink message(%s) from PID(%d)\n", (char*)nlmsg_data(nlh), pid);

    // sending to user process
    msg_size=strlen(msg);
    skb_out = nlmsg_new(msg_size, 0);
    nlh=nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
    NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */
    strncpy(nlmsg_data(nlh), msg, msg_size);
    nlmsg_unicast(nl_sock, skb_out, pid);
}

struct netlink_kernel_cfg cfg = {
    .input = nl_recv_msg,
};

static int __init netlink_module_init(void)
{
  printk(KERN_INFO "NETLINK TEST START\n");
  nl_sock = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);
  return 0;
}

static void __exit netlink_module_exit(void)
{
  printk(KERN_INFO "NETLINK TEST FINISH\n");
  netlink_kernel_release(nl_sock);
}

module_init(netlink_module_init);
module_exit(netlink_module_exit);

MODULE_AUTHOR("hana_shin");
MODULE_LICENSE("GPL v2");
