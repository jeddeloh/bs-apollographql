module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__Errors_ApolloError;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module Graphql = ApolloClient__Graphql;
module LazyQueryHookOptions = ApolloClient__React_Types.LazyQueryHookOptions;
module QueryTuple = ApolloClient__React_Types.QueryTuple;
module QueryTuple__noVariables = ApolloClient__React_Types.QueryTuple__noVariables;
module Types = ApolloClient__Types;
module Utils = ApolloClient__Utils;
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;

module type Operation = Types.Operation;
module type OperationNoRequiredVars = Types.OperationNoRequiredVars;

module Js_ = {
  // export declare function useLazyQuery<TData = any, TVariables = OperationVariables>(query: DocumentNode, options?: LazyQueryHookOptions<TData, TVariables>): QueryTuple<TData, TVariables>;
  [@bs.module "@apollo/client"]
  external useLazyQuery:
    (
      . Graphql.documentNode,
      LazyQueryHookOptions.Js_.t('jsData, 'jsVariables)
    ) =>
    QueryTuple.Js_.t('jsData, 'variables, 'jsVariables) =
    "useLazyQuery";
};

let useLazyQuery:
  type data jsData variables jsVariables.
    (
      ~query: (module Operation with
                 type t = data and
                 type Raw.t = jsData and
                 type t_variables = variables and
                 type Raw.t_variables = jsVariables),
      ~client: ApolloClient.t=?,
      ~context: Js.Json.t=?,
      ~displayName: string=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      ~notifyOnNetworkStatusChange: bool=?,
      ~onCompleted: data => unit=?,
      ~onError: ApolloError.t => unit=?,
      ~partialRefetch: bool=?,
      ~pollInterval: int=?,
      ~ssr: bool=?,
      unit
    ) =>
    QueryTuple.t(data, jsData, variables, jsVariables) =
  (
    ~query as (module Operation),
    ~client=?,
    ~context=?,
    ~displayName=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~notifyOnNetworkStatusChange=?,
    ~onCompleted=?,
    ~onError=?,
    ~partialRefetch=?,
    ~pollInterval=?,
    ~ssr=?,
    (),
  ) => {
    let jsQueryTuple =
      Js_.useLazyQuery(.
        Operation.query,
        LazyQueryHookOptions.toJs(
          {
            client,
            context,
            displayName,
            errorPolicy,
            fetchPolicy,
            onCompleted,
            onError,
            notifyOnNetworkStatusChange,
            partialRefetch,
            pollInterval,
            query: None,
            ssr,
            variables: None,
          },
          ~parse=Operation.parse,
        ),
      );

    Utils.useGuaranteedMemo1(
      () => {
        jsQueryTuple->QueryTuple.fromJs(
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
          ~serializeVariables=Operation.serializeVariables,
        )
      },
      jsQueryTuple,
    );
  };

let useLazyQueryWithVariables:
  type data jsData variables jsVariables.
    (
      ~query: (module Operation with
                 type t = data and
                 type Raw.t = jsData and
                 type t_variables = variables and
                 type Raw.t_variables = jsVariables),
      ~client: ApolloClient.t=?,
      ~context: Js.Json.t=?,
      ~displayName: string=?,
      ~errorPolicy: ErrorPolicy.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      ~mapJsVariables: jsVariables => jsVariables=?,
      ~notifyOnNetworkStatusChange: bool=?,
      ~onCompleted: data => unit=?,
      ~onError: ApolloError.t => unit=?,
      ~partialRefetch: bool=?,
      ~pollInterval: int=?,
      ~ssr: bool=?,
      variables
    ) =>
    QueryTuple__noVariables.t(data, jsData, jsVariables) =
  (
    ~query as (module Operation),
    ~client=?,
    ~context=?,
    ~displayName=?,
    ~errorPolicy=?,
    ~fetchPolicy=?,
    ~mapJsVariables=Utils.identity,
    ~notifyOnNetworkStatusChange=?,
    ~onCompleted=?,
    ~onError=?,
    ~partialRefetch=?,
    ~pollInterval=?,
    ~ssr=?,
    variables,
  ) => {
    let jsVariables =
      variables->Operation.serializeVariables->mapJsVariables;

    let jsQueryTuple =
      Js_.useLazyQuery(.
        Operation.query,
        LazyQueryHookOptions.toJs(
          {
            client,
            context,
            displayName,
            errorPolicy,
            fetchPolicy,
            onCompleted,
            onError,
            notifyOnNetworkStatusChange,
            partialRefetch,
            pollInterval,
            query: None,
            ssr,
            variables: Some(jsVariables),
          },
          ~parse=Operation.parse,
        ),
      );

    Utils.useGuaranteedMemo1(
      () => {
        jsQueryTuple->QueryTuple__noVariables.fromJs(
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
          // Passing in the same variables from above allows us to reuse some types
          ~variables=jsVariables,
        )
      },
      jsQueryTuple,
    );
  };
