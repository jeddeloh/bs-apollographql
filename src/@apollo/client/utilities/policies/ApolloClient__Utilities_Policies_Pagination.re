module FieldPolicy = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldPolicy;
module KeyArgs = ApolloClient__Cache_InMemory_Policies_FieldPolicy.FieldPolicy_KeyArgs;

// declare type TInternalRelay<TNode> = Readonly<{
//     edges: Array<{
//         cursor: string;
//         node: TNode;
//     }>;
//     pageInfo: Readonly<{
//         hasPreviousPage: boolean;
//         hasNextPage: boolean;
//         startCursor: string;
//         endCursor: string;
//     }>;
// }>;

module Js_ = {
  // export declare function concatPagination<T = Reference>(keyArgs?: KeyArgs): FieldPolicy<T[]>;
  [@bs.module "@apollo/client/utilities"] [@bs.val]
  external concatPagination: (. option(KeyArgs.Js_.t)) => FieldPolicy.Js_.t =
    "concatPagination";

  // export declare function offsetLimitPagination<T = Reference>(keyArgs?: KeyArgs): FieldPolicy<T[]>;
  [@bs.module "@apollo/client/utilities"] [@bs.val]
  external offsetLimitPagination:
    (. option(KeyArgs.Js_.t)) => FieldPolicy.Js_.t =
    "offsetLimitPagination";

  // export declare function relayStylePagination<TNode = Reference>(keyArgs?: KeyArgs): FieldPolicy<TInternalRelay<TNode>>;
  [@bs.module "@apollo/client/utilities"] [@bs.val]
  external relayStylePagination:
    (. option(KeyArgs.Js_.t)) => FieldPolicy.Js_.t =
    "relayStylePagination";
};

let concatPagination: KeyArgs.t => FieldPolicy.Js_.t =
  keyArgs => Js_.concatPagination(. Some(keyArgs->KeyArgs.toJs));

let offsetLimitPagination: KeyArgs.t => FieldPolicy.Js_.t =
  keyArgs => Js_.offsetLimitPagination(. Some(keyArgs->KeyArgs.toJs));

let relayStylePagination: KeyArgs.t => FieldPolicy.Js_.t =
  keyArgs => Js_.relayStylePagination(. Some(keyArgs->KeyArgs.toJs));
