module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__Errors_ApolloError;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module Graphql = ApolloClient__Graphql;
module QueryHookOptions = ApolloClient__React_Types.QueryHookOptions;
module QueryResult = ApolloClient__React_Types.QueryResult;
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription;
module Types = ApolloClient__Types;
module Utils = ApolloClient__Utils;
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;

module type Operation = Types.Operation;
module type OperationNoRequiredVars = Types.OperationNoRequiredVars;

module Js_ = {
  // export declare function useQuery<TData = any, TVariables = OperationVariables>(query: DocumentNode, options?: QueryHookOptions<TData, TVariables>): QueryResult<TData, TVariables>;
  [@bs.module "@apollo/client"]
  external useQuery:
    (. Graphql.documentNode, QueryHookOptions.Js_.t('jsData, 'jsVariables)) =>
    QueryResult.Js_.t('jsData, 'jsVariables) =
    "useQuery";
};

let useQuery:
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
      ~skip: bool=?,
      ~ssr: bool=?,
      variables
    ) =>
    QueryResult.t(data, jsData, jsVariables) =
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
    ~skip=?,
    ~ssr=?,
    variables,
  ) => {
    let jsVariables =
      variables->Operation.serializeVariables->mapJsVariables;

    let jsQueryResult =
      Js_.useQuery(.
        Operation.query,
        QueryHookOptions.toJs(
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
            skip,
            ssr,
            variables: jsVariables,
          },
          ~parse=Operation.parse,
        ),
      );

    Utils.useGuaranteedMemo1(
      () => {
        jsQueryResult->QueryResult.fromJs(
          ~parse=Operation.parse,
          ~serialize=Operation.serialize,
        )
      },
      jsQueryResult,
    );
  };

module Extend = (M: Operation) => {
  let refetchQueryDescription:
    (
      ~context: Js.Json.t=?,
      ~mapJsVariables: 'jsVariables => 'jsVariables=?,
      M.t_variables
    ) =>
    RefetchQueryDescription.t_variant =
    (~context=?, ~mapJsVariables=Utils.identity, variables) => {
      let jsVariables = variables->M.serializeVariables->mapJsVariables;

      RefetchQueryDescription.PureQueryOptions({
        query: M.query,
        variables: jsVariables,
        context,
      });
    };

  let use =
      (
        ~client=?,
        ~context=?,
        ~displayName=?,
        ~errorPolicy=?,
        ~fetchPolicy=?,
        ~mapJsVariables=?,
        ~notifyOnNetworkStatusChange=?,
        ~onCompleted=?,
        ~onError=?,
        ~partialRefetch=?,
        ~pollInterval=?,
        ~skip=?,
        ~ssr=?,
        variables,
      ) => {
    useQuery(
      ~query=(module M),
      ~client?,
      ~context?,
      ~displayName?,
      ~errorPolicy?,
      ~fetchPolicy?,
      ~mapJsVariables?,
      ~notifyOnNetworkStatusChange?,
      ~onCompleted?,
      ~onError?,
      ~partialRefetch?,
      ~pollInterval?,
      ~skip?,
      ~ssr?,
      variables,
    );
  };

  let useLazy =
      (
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
    ApolloClient__React_Hooks_UseLazyQuery.useLazyQuery(
      ~query=(module M),
      ~client?,
      ~context?,
      ~displayName?,
      ~errorPolicy?,
      ~fetchPolicy?,
      ~notifyOnNetworkStatusChange?,
      ~onCompleted?,
      ~onError?,
      ~partialRefetch?,
      ~pollInterval?,
      ~ssr?,
      (),
    );
  };

  let useLazyWithVariables =
      (
        ~client=?,
        ~context=?,
        ~displayName=?,
        ~errorPolicy=?,
        ~fetchPolicy=?,
        ~mapJsVariables=?,
        ~notifyOnNetworkStatusChange=?,
        ~onCompleted=?,
        ~onError=?,
        ~partialRefetch=?,
        ~pollInterval=?,
        ~ssr=?,
        variables,
      ) => {
    ApolloClient__React_Hooks_UseLazyQuery.useLazyQueryWithVariables(
      ~query=(module M),
      ~client?,
      ~context?,
      ~displayName?,
      ~errorPolicy?,
      ~fetchPolicy?,
      ~mapJsVariables?,
      ~notifyOnNetworkStatusChange?,
      ~onCompleted?,
      ~onError?,
      ~partialRefetch?,
      ~pollInterval?,
      ~ssr?,
      variables,
    );
  };
};
