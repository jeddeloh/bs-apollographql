module ApolloClient = ApolloClient__ApolloClient;
module ApolloError = ApolloClient__Errors_ApolloError;
module ApolloQueryResult = ApolloClient__Core_Types.ApolloQueryResult;
module ErrorPolicy = ApolloClient__Core_WatchQueryOptions.ErrorPolicy;
module FetchPolicy = ApolloClient__Core_WatchQueryOptions.FetchPolicy;
module FetchPolicy__noCacheExtracted = ApolloClient__Core_WatchQueryOptions.FetchPolicy__noCacheExtracted;
module FetchResult = ApolloClient__Link_Core_Types.FetchResult;
module Graphql = ApolloClient__Graphql;
module MutationUpdaterFn = ApolloClient__Core_WatchQueryOptions.MutationUpdaterFn;
module NetworkStatus = ApolloClient__Core_NetworkStatus.NetworkStatus;
module RefetchQueryDescription = ApolloClient__Core_WatchQueryOptions.RefetchQueryDescription;
module SubscribeToMoreOptions = ApolloClient__Core_WatchQueryOptions.SubscribeToMoreOptions;
module Types = ApolloClient__Types;
module UpdateQueryFn = ApolloClient__Core_WatchQueryOptions.UpdateQueryFn;
module Utils = ApolloClient__Utils;
module WatchQueryFetchPolicy = ApolloClient__Core_WatchQueryOptions.WatchQueryFetchPolicy;

module type Operation = Types.Operation;

module QueryHookOptions = {
  module Js_ = {
    // export interface QueryHookOptions<TData = any, TVariables = OperationVariables> extends QueryFunctionOptions<TData, TVariables> {
    //     query?: DocumentNode;
    // }
    type t('jsData, 'jsVariables) = {
      query: option(Graphql.documentNode),
      // ...extends QueryFunctionOptions
      displayName: option(string),
      skip: option(bool),
      onCompleted: option('jsData => unit),
      onError: option((. ApolloError.Js_.t) => unit),
      // ..extends BaseQueryOptions
      client: option(ApolloClient.t),
      context: option(Js.Json.t), // ACTUAL: Record<string, any>
      errorPolicy: option(string),
      fetchPolicy: option(string),
      notifyOnNetworkStatusChange: option(bool),
      partialRefetch: option(bool),
      pollInterval: option(int),
      // INTENTIONALLY IGNORED
      // returnPartialData: option(bool),
      ssr: option(bool),
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
    };
  };

  type t('data, 'jsVariables) = {
    query: option(Graphql.documentNode),
    // ...extends QueryFunctionOptions
    displayName: option(string),
    skip: option(bool),
    onCompleted: option('data => unit),
    onError: option(ApolloError.t => unit),
    // ...extends BaseQueryOptions
    client: option(ApolloClient.t),
    context: option(Js.Json.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(WatchQueryFetchPolicy.t),
    notifyOnNetworkStatusChange: option(bool),
    partialRefetch: option(bool),
    pollInterval: option(int),
    // INTENTIONALLY IGNORED
    // returnPartialData: option(bool),
    ssr: option(bool),
    variables: 'jsVariables,
  };

  let toJs =
      (t: t('data, 'jsVariables), ~parse: 'jsData => 'data)
      : Js_.t('jsData, 'jsVariables) => {
    client: t.client,
    context: t.context,
    displayName: t.displayName,
    errorPolicy: t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
    onCompleted:
      t.onCompleted
      ->Belt.Option.map((onCompleted, jsData) => onCompleted(jsData->parse)),
    onError:
      t.onError
      ->Belt.Option.map(onError =>
          (. jsApolloError) => onError(ApolloError.fromJs(jsApolloError))
        ),
    fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
    notifyOnNetworkStatusChange: t.notifyOnNetworkStatusChange,
    query: t.query,
    pollInterval: t.pollInterval,
    partialRefetch: t.partialRefetch,
    skip: t.skip,
    ssr: t.ssr,
    variables: t.variables,
  };
};

module LazyQueryHookOptions = {
  module Js_ = {
    // export interface LazyQueryHookOptions<TData = any, TVariables = OperationVariables> extends Omit<QueryFunctionOptions<TData, TVariables>, 'skip'> {
    //     query?: DocumentNode;
    // }
    [@bs.deriving abstract]
    type t('jsData, 'jsVariables) = {
      [@bs.optional]
      query: Graphql.documentNode,
      // ...extends QueryFunctionOptions
      [@bs.optional]
      displayName: string,
      [@bs.optional]
      onCompleted: 'jsData => unit,
      [@bs.optional]
      onError: (. ApolloError.Js_.t) => unit,
      // ..extends BaseQueryOptions
      [@bs.optional]
      client: ApolloClient.t,
      [@bs.optional]
      context: Js.Json.t, // ACTUAL: Record<string, any>
      [@bs.optional]
      errorPolicy: string,
      [@bs.optional]
      fetchPolicy: string,
      [@bs.optional]
      notifyOnNetworkStatusChange: bool,
      [@bs.optional]
      partialRefetch: bool,
      [@bs.optional]
      pollInterval: int,
      // INTENTIONALLY IGNORED
      // returnPartialData: option(bool),
      [@bs.optional]
      ssr: bool,
      [@bs.optional]
      variables: 'jsVariables,
    };
    let make = t;
  };

  type t('data, 'jsVariables) = {
    query: option(Graphql.documentNode),
    // ...extends QueryFunctionOptions
    displayName: option(string),
    onCompleted: option('data => unit),
    onError: option(ApolloError.t => unit),
    // ...extends BaseQueryOptions
    client: option(ApolloClient.t),
    context: option(Js.Json.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(WatchQueryFetchPolicy.t),
    notifyOnNetworkStatusChange: option(bool),
    partialRefetch: option(bool),
    pollInterval: option(int),
    // INTENTIONALLY IGNORED
    // returnPartialData: option(bool),
    ssr: option(bool),
    variables: option('jsVariables),
  };

  let toJs =
      (t: t('data, 'jsVariables), ~parse: 'jsData => 'data)
      : Js_.t('jsData, 'jsVariables) =>
    Js_.make(
      ~client=?t.client,
      ~context=?t.context,
      ~displayName=?t.displayName,
      ~errorPolicy=?t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
      ~onCompleted=?
        t.onCompleted
        ->Belt.Option.map((onCompleted, jsData) =>
            onCompleted(jsData->parse)
          ),
      ~onError=?
        t.onError
        ->Belt.Option.map(onError =>
            (. jsApolloError) => onError(ApolloError.fromJs(jsApolloError))
          ),
      ~fetchPolicy=?
        t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
      ~notifyOnNetworkStatusChange=?t.notifyOnNetworkStatusChange,
      ~query=?t.query,
      ~pollInterval=?t.pollInterval,
      ~partialRefetch=?t.partialRefetch,
      ~ssr=?t.ssr,
      ~variables=?t.variables,
      (),
    );
};
module QueryLazyOptions = {
  module Js_ = {
    // export interface QueryLazyOptions<TVariables> {
    //     variables?: TVariables;
    //     context?: Context;
    // }
    type t('jsVariables) = {
      variables: 'jsVariables,
      context: option(Js.Json.t),
    };
  };

  type t('jsVariables) = Js_.t('jsVariables);
};

module QueryResult = {
  type useMethodFunctionsInThisModuleInstead;

  module Js_ = {
    type t_fetchMoreOptions_updateQueryOptions('jsData, 'jsVariables) = {
      fetchMoreResult: option('jsData),
      variables: option('jsVariables),
    };

    // We use abstract because Apollo is looking at query key, not just value
    [@bs.deriving abstract]
    type t_fetchMoreOptions('jsData, 'jsVariables) = {
      [@bs.optional]
      query: Graphql.Language.documentNode,
      // ...extends FetchMoreQueryOptions
      [@bs.optional]
      variables: 'jsVariables,
      [@bs.optional]
      context: Js.Json.t,
      // ...extends FetchMoreOptions
      [@bs.optional]
      updateQuery:
        (
          . 'jsData,
          t_fetchMoreOptions_updateQueryOptions('jsData, 'jsVariables)
        ) =>
        'jsData,
    };

    type t_updateQueryOptions('jsVariables) = {variables: 'jsVariables};

    // export interface QueryResult<TData = any, TVariables = OperationVariables> extends ObservableQueryFields<TData, TVariables> {
    //     client: ApolloClient<any>;
    //     data: TData | undefined;
    //     error?: ApolloError;
    //     loading: boolean;
    //     networkStatus: NetworkStatus;
    //     called: true;
    // }
    type t('jsData, 'jsVariables) = {
      called: bool,
      client: ApolloClient.t,
      data: option('jsData),
      error: option(ApolloError.Js_.t),
      loading: bool,
      networkStatus: NetworkStatus.t,
      // ...extends ObservableQueryFields<TData, TVariables> = Pick<ObservableQuery<TData, TVariables>, 'startPolling' | 'stopPolling' | 'subscribeToMore' | 'updateQuery' | 'refetch' | 'jsVariables'>
      fetchMore: useMethodFunctionsInThisModuleInstead,
      refetch: useMethodFunctionsInThisModuleInstead,
      startPolling: useMethodFunctionsInThisModuleInstead,
      stopPolling: useMethodFunctionsInThisModuleInstead,
      subscribeToMore: useMethodFunctionsInThisModuleInstead,
      updateQuery: useMethodFunctionsInThisModuleInstead,
      variables: 'jsVariables,
    };

    [@bs.send]
    external fetchMore:
      (
        t('jsData, 'jsVariables),
        t_fetchMoreOptions('jsData, 'jsVariables)
      ) =>
      Js.Promise.t(ApolloQueryResult.Js_.t('jsData)) =
      "fetchMore";

    [@bs.send]
    external refetch:
      (t('jsData, 'jsVariables), 'jsVariables) =>
      Js.Promise.t(ApolloQueryResult.Js_.t('jsData)) =
      "refetch";

    [@bs.send]
    external startPolling: (t('jsData, 'jsVariables), int) => unit =
      "startPolling";

    [@bs.send]
    external stopPolling: (t('jsData, 'jsVariables), unit) => unit =
      "stopPolling";

    [@bs.send]
    external updateQuery:
      (
        t('jsData, 'jsVariables),
        ('jsData, t_updateQueryOptions('jsVariables)) => 'jsData
      ) =>
      unit =
      "updateQuery";

    // subscribeToMore<TSubscriptionData = TData, TSubscriptionVariables = TVariables>(options: SubscribeToMoreOptions<TData, TSubscriptionVariables, TSubscriptionData>): () => void;
    [@bs.send]
    external subscribeToMore:
      (
        t('jsData, 'jsVariables),
        SubscribeToMoreOptions.Js_.t(
          'jsData,
          'subscriptionVariables,
          'jsSubscriptionData,
        )
      ) =>
      unit =
      "subscribeToMore";
  };

  type t_updateQueryOptions('jsVariables) =
    Js_.t_updateQueryOptions('jsVariables);

  type t_fetchMoreOptions_updateQueryOptions('data, 'jsVariables) = {
    fetchMoreResult: option('data),
    variables: option('jsVariables),
  };

  type t_fetchMoreOptions('data, 'jsVariables) = {
    query: option(Graphql.Language.documentNode),
    // ...extends FetchMoreQueryOptions
    variables: option('jsVariables),
    context: option(Js.Json.t),
    // ...extends FetchMoreOptions
    updateQuery:
      option(
        ('data, t_fetchMoreOptions_updateQueryOptions('data, 'jsVariables)) =>
        'data,
      ),
  };

  type t('data, 'jsData, 'jsVariables) = {
    called: bool,
    client: ApolloClient.t,
    data: option('data),
    error: option(ApolloError.t),
    loading: bool,
    networkStatus: NetworkStatus.t,
    fetchMore: useMethodFunctionsInThisModuleInstead,
    refetch: useMethodFunctionsInThisModuleInstead,
    startPolling: useMethodFunctionsInThisModuleInstead,
    stopPolling: useMethodFunctionsInThisModuleInstead,
    subscribeToMore: useMethodFunctionsInThisModuleInstead,
    updateQuery: useMethodFunctionsInThisModuleInstead,
    __parse: 'jsData => 'data,
    __serialize: 'data => 'jsData,
  };

  external unsafeCastForMethod:
    t('data, 'jsData, 'jsVariables) => Js_.t('jsData, 'jsVariables) =
    "%identity";

  let fromJs:
    (
      Js_.t('jsData, 'jsVariables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    t('data, 'jsData, 'jsVariables) =
    (js, ~parse, ~serialize) => {
      called: js.called,
      client: js.client,
      data: js.data->Belt.Option.map(parse),
      error: js.error->Belt.Option.map(ApolloError.fromJs),
      loading: js.loading,
      networkStatus: js.networkStatus,
      fetchMore: js.fetchMore,
      refetch: js.refetch,
      startPolling: js.startPolling,
      stopPolling: js.stopPolling,
      subscribeToMore: js.subscribeToMore,
      updateQuery: js.updateQuery,
      __parse: parse,
      __serialize: serialize,
    };

  let fetchMore:
    (
      t('queryData, 'jsQueryData, 'jsVariables),
      ~context: Js.Json.t=?,
      ~variables: 'jsVariables=?,
      ~updateQuery: (
                      'data,
                      t_fetchMoreOptions_updateQueryOptions(
                        'data,
                        'jsVariables,
                      )
                    ) =>
                    'data
                      =?,
      unit
    ) =>
    Js.Promise.t(ApolloQueryResult.t('data)) =
    (queryResult, ~context=?, ~variables=?, ~updateQuery=?, ()) => {
      let serialize = queryResult.__serialize;
      let parse = queryResult.__parse;

      queryResult
      ->unsafeCastForMethod
      ->Js_.fetchMore(
          Js_.t_fetchMoreOptions(
            ~context?,
            ~updateQuery=?
              updateQuery->Belt.Option.map(updateQuery =>
                (.
                  previousResult,
                  jsFetchMoreOptions:
                    Js_.t_fetchMoreOptions_updateQueryOptions(
                      'jsData,
                      'jsVariables,
                    ),
                ) =>
                  updateQuery(
                    parse(previousResult),
                    {
                      fetchMoreResult:
                        jsFetchMoreOptions.fetchMoreResult
                        ->Belt.Option.map(parse),
                      variables: jsFetchMoreOptions.variables,
                    },
                  )
                  ->serialize
              ),
            ~variables?,
            (),
          ),
        )
      ->Js.Promise.then_(
          jsResult =>
            Js.Promise.resolve(ApolloQueryResult.fromJs(jsResult, ~parse)),
          _,
        );
    };

  let refetch:
    (t('data, 'jsData, 'jsVariables), 'jsVariables) =>
    Js.Promise.t(ApolloQueryResult.t('data)) =
    (queryResult, variables) =>
      queryResult
      ->unsafeCastForMethod
      ->Js_.refetch(variables)
      ->Js.Promise.then_(
          jsApolloQueryResult =>
            Js.Promise.resolve(
              jsApolloQueryResult->ApolloQueryResult.fromJs(
                ~parse=queryResult.__parse,
              ),
            ),
          _,
        );

  [@bs.send]
  external startPolling: (t('data, 'jsData, 'jsVariables), int) => unit =
    "startPolling";

  [@bs.send]
  external stopPolling: (t('data, 'jsData, 'jsVariables), unit) => unit =
    "stopPolling";

  let subscribeToMore:
    type subscriptionData subscriptionVariables.
      (
        t('queryData, 'jsQueryData, 'jsVariables),
        ~subscription: (module Operation with
                          type t = subscriptionData and
                          type Raw.t_variables = subscriptionVariables),
        ~updateQuery: UpdateQueryFn.t(
                        'queryData,
                        subscriptionVariables,
                        subscriptionData,
                      )
                        =?,
        ~onError: Js.Exn.t => unit=?,
        ~context: Js.Json.t=?,
        subscriptionVariables
      ) =>
      unit =
    (
      queryResult,
      ~subscription as (module Operation),
      ~updateQuery=?,
      ~onError=?,
      ~context=?,
      variables,
    ) => {
      queryResult
      ->unsafeCastForMethod
      ->Js_.subscribeToMore(
          SubscribeToMoreOptions.toJs(
            {
              document: Operation.query,
              variables,
              updateQuery,
              onError,
              context,
            },
            ~queryParse=queryResult.__parse,
            ~querySerialize=queryResult.__serialize,
            ~subscriptionParse=Operation.parse,
          ),
        );
    };

  let updateQuery:
    (
      t('data, 'jsData, 'jsVariables),
      ('data, t_updateQueryOptions('jsVariables)) => 'data
    ) =>
    unit =
    (queryResult, updateQueryFn) => {
      let parse = queryResult.__parse;
      let serialize = queryResult.__serialize;
      queryResult
      ->unsafeCastForMethod
      ->Js_.updateQuery((jsPreviousData, options) => {
          updateQueryFn(jsPreviousData->parse, options)->serialize
        });
    };
};

module UnexecutedLazyResult = {
  module Js_ = {
    // declare type UnexecutedLazyFields = {
    //     loading: false;
    //     networkStatus: NetworkStatus.ready;
    //     called: false;
    //     data: undefined;
    // };
    // declare type UnexecutedLazyResult = UnexecutedLazyFields & AbsentLazyResultFields;
    type t = {
      loading: bool,
      networkStatus: NetworkStatus.Js_.t,
      called: bool,
    };
  };
  type t = {
    loading: bool,
    networkStatus: NetworkStatus.t,
    called: bool,
  };

  let fromJs: Js_.t => t =
    js => {
      loading: js.loading,
      networkStatus: js.networkStatus->NetworkStatus.fromJs,
      called: js.called,
    };
};

module LazyQueryResult = {
  module Js_ = {
    module Union: {
      type t;
      let unexecutedLazyResult: UnexecutedLazyResult.Js_.t => t;
      let queryResult: QueryResult.Js_.t('jsData, 'jsVariables) => t;
      type case('jsData, 'jsVariables) =
        | UnexecutedLazyResult(UnexecutedLazyResult.Js_.t)
        | QueryResult(QueryResult.Js_.t('jsData, 'jsVariables));
      let classify: t => case('jsData, 'jsVariables);
    } = {
      [@unboxed]
      type t =
        | Any('a): t;
      let unexecutedLazyResult = (v: UnexecutedLazyResult.Js_.t) => Any(v);
      let queryResult = (v: QueryResult.Js_.t('jsData, 'jsVariables)) =>
        Any(v);
      type case('jsData, 'jsVariables) =
        | UnexecutedLazyResult(UnexecutedLazyResult.Js_.t)
        | QueryResult(QueryResult.Js_.t('jsData, 'jsVariables));
      let classify = (Any(v): t): case('jsData, 'jsVariables) =>
        if ([%raw {|function (value) { return "client" in value}|}](v)) {
          QueryResult(
            Obj.magic(v): QueryResult.Js_.t('jsData, 'jsVariables),
          );
        } else {
          UnexecutedLazyResult(Obj.magic(v): UnexecutedLazyResult.Js_.t);
        };
    };
    // export declare type LazyQueryResult<TData, TVariables> = UnexecutedLazyResult | QueryResult<TData, TVariables>;
    type t('jsData, 'jsVariables) = Union.t;
  };

  type t('data, 'jsData, 'jsVariables) =
    | Executed(QueryResult.t('data, 'jsData, 'jsVariables))
    | Unexecuted(UnexecutedLazyResult.t);

  let fromJs:
    (
      Js_.t('jsData, 'jsVariables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    t('data, 'jsData, 'jsVariables) =
    (js, ~parse, ~serialize) => {
      switch (js->Js_.Union.classify) {
      | UnexecutedLazyResult(v) => Unexecuted(v->UnexecutedLazyResult.fromJs)
      | QueryResult(v) => Executed(v->QueryResult.fromJs(~parse, ~serialize))
      };
    };
};

module QueryTuple = {
  module Js_ = {
    // export declare type QueryTuple<TData, TVariables> = [(options?: QueryLazyOptions<TVariables>) => void, LazyQueryResult<TData, TVariables>];
    type t('jsData, 'variables, 'jsVariables) = (
      QueryLazyOptions.Js_.t('jsVariables) => unit,
      LazyQueryResult.Js_.t('jsData, 'jsVariables),
    );
  };

  type t('data, 'jsData, 'variables, 'jsVariables) = (
    (
      ~context: Js.Json.t=?,
      ~mapJsVariables: 'jsVariables => 'jsVariables=?,
      'variables
    ) =>
    unit,
    LazyQueryResult.t('data, 'jsData, 'jsVariables),
  );

  let fromJs:
    (
      Js_.t('jsData, 'variables, 'jsVariables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData,
      ~serializeVariables: 'variables => 'jsVariables
    ) =>
    t('data, 'jsData, 'variables, 'jsVariables) =
    (
      (jsExecuteQuery, jsLazyQueryResult),
      ~parse,
      ~serialize,
      ~serializeVariables,
    ) => (
      (~context=?, ~mapJsVariables=ApolloClient__Utils.identity, variables) =>
        jsExecuteQuery({
          context,
          variables: variables->serializeVariables->mapJsVariables,
        }),
      jsLazyQueryResult->LazyQueryResult.fromJs(~parse, ~serialize),
    );
};

module QueryTuple__noVariables = {
  module Js_ = {
    type t('jsData, 'variables, 'jsVariables) =
      QueryTuple.Js_.t('jsData, 'variables, 'jsVariables);
  };

  type t('data, 'jsData, 'jsVariables) = (
    (~context: Js.Json.t=?, unit) => unit,
    LazyQueryResult.t('data, 'jsData, 'jsVariables),
  );

  let fromJs:
    (
      Js_.t('jsData, 'variables, 'jsVariables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData,
      ~variables: 'jsVariables
    ) =>
    t('data, 'jsData, 'jsVariables) =
    ((jsExecuteQuery, jsLazyQueryResult), ~parse, ~serialize, ~variables) => (
      (~context=?, ()) => jsExecuteQuery({context, variables}),
      jsLazyQueryResult->LazyQueryResult.fromJs(~parse, ~serialize),
    );
};

module BaseMutationOptions = {
  module Js_ = {
    // export interface BaseMutationOptions<TData = any, TVariables = OperationVariables> {
    //     awaitRefetchQueries?: boolean;
    //     client?: ApolloClient<object>;
    //     context?: Context;
    //     errorPolicy?: ErrorPolicy;
    //     fetchPolicy?: Extract<WatchQueryFetchPolicy, 'no-cache'>;
    //     ignoreResults?: boolean;
    //     onCompleted?: (data: TData) => void;
    //     onError?: (error: ApolloError) => void;
    //     optimisticResponse?: TData | ((vars: TVariables) => TData);
    //     notifyOnNetworkStatusChange?: boolean;
    //     refetchQueries?: Array<string | PureQueryOptions> | RefetchQueriesFunction;
    //     update?: MutationUpdaterFn<TData>;
    //     variables?: TVariables;
    // }
    type t('jsData, 'jsVariables) = {
      awaitRefetchQueries: option(bool),
      client: option(ApolloClient.Js_.t),
      context: option(Js.Json.t), // actual: option(Context)
      errorPolicy: option(ErrorPolicy.Js_.t),
      fetchPolicy: option(FetchPolicy__noCacheExtracted.Js_.t),
      ignoreResults: option(bool),
      notifyOnNetworkStatusChange: option(bool),
      onError: option(ApolloError.Js_.t => unit),
      optimisticResponse: option('jsVariables => 'jsData),
      refetchQueries: option(RefetchQueryDescription.Js_.t),
      update: option(MutationUpdaterFn.Js_.t('jsData)),
      variables: option('jsVariables),
    };
  };

  type t('data, 'jsVariables) = {
    awaitRefetchQueries: option(bool),
    context: option(Js.Json.t),
    client: option(ApolloClient.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(FetchPolicy__noCacheExtracted.t),
    ignoreResults: option(bool),
    notifyOnNetworkStatusChange: option(bool),
    onError: option(ApolloError.t => unit),
    onCompleted: option('data => unit),
    optimisticResponse: option('jsVariables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    update: option(MutationUpdaterFn.t('data)),
    variables: option('jsVariables),
  };
};

module MutationHookOptions = {
  module Js_ = {
    // export interface MutationHookOptions<TData = any, TVariables = OperationVariables> extends BaseMutationOptions<TData, TVariables> {
    //   mutation?: DocumentNode;
    // }
    /**
     * We use deriving abstract here because option('jsVariables) is not typesafe,
     * but still needs to be optional since a user has the option of providing
     * the variables to the results of the hook rather than the hook itself
     */
    [@bs.deriving abstract]
    type t('jsData, 'jsVariables) = {
      [@bs.optional]
      mutation: Graphql.documentNode,
      // ...extends BaseMutationOptions
      [@bs.optional]
      awaitRefetchQueries: bool,
      [@bs.optional]
      client: ApolloClient.Js_.t,
      [@bs.optional]
      context: Js.Json.t, // actual: option(Context)
      [@bs.optional]
      errorPolicy: ErrorPolicy.Js_.t,
      [@bs.optional]
      fetchPolicy: FetchPolicy__noCacheExtracted.Js_.t,
      [@bs.optional]
      ignoreResults: bool,
      [@bs.optional]
      notifyOnNetworkStatusChange: bool,
      [@bs.optional]
      onError: (. ApolloError.Js_.t) => unit,
      [@bs.optional]
      optimisticResponse: 'jsVariables => 'jsData,
      [@bs.optional]
      refetchQueries: RefetchQueryDescription.Js_.t,
      [@bs.optional]
      update: MutationUpdaterFn.Js_.t('jsData),
      [@bs.optional]
      variables: 'jsVariables,
    };
    let make = t;
  };

  type t('data, 'jsVariables) = {
    mutation: option(Graphql.documentNode),
    awaitRefetchQueries: option(bool),
    context: option(Js.Json.t),
    client: option(ApolloClient.t),
    errorPolicy: option(ErrorPolicy.t),
    fetchPolicy: option(FetchPolicy__noCacheExtracted.t),
    ignoreResults: option(bool),
    notifyOnNetworkStatusChange: option(bool),
    onError: option(ApolloError.t => unit),
    onCompleted: option('data => unit),
    optimisticResponse: option('jsVariables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    update: option(MutationUpdaterFn.t('data)),
    variables: option('jsVariables),
  };

  let toJs:
    (
      t('data, 'jsVariables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    Js_.t('jsData, 'jsVariables) =
    (t, ~parse, ~serialize) => {
      Js_.make(
        ~awaitRefetchQueries=?t.awaitRefetchQueries,
        ~context=?t.context,
        ~client=?t.client,
        ~errorPolicy=?t.errorPolicy->Belt.Option.map(ErrorPolicy.toJs),
        ~fetchPolicy=?
          t.fetchPolicy->Belt.Option.map(FetchPolicy__noCacheExtracted.toJs),
        ~ignoreResults=?t.ignoreResults,
        ~mutation=?t.mutation,
        ~notifyOnNetworkStatusChange=?t.notifyOnNetworkStatusChange,
        ~onError=?
          t.onError
          ->Belt.Option.map(onError =>
              (. jsApolloError) =>
                onError(ApolloError.fromJs(jsApolloError))
            ),
        ~optimisticResponse=?
          t.optimisticResponse
          ->Belt.Option.map((optimisticResponse, variables) =>
              optimisticResponse(variables)->serialize
            ),
        ~refetchQueries=?
          t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
        ~update=?t.update->Belt.Option.map(MutationUpdaterFn.toJs(~parse)),
        ~variables=?t.variables,
        (),
      );
    };
};

module MutationResult = {
  module Js_ = {
    // export interface MutationResult<TData = any> {
    //     data?: TData | null;
    //     error?: ApolloError;
    //     loading: boolean;
    //     called: boolean;
    //     client?: ApolloClient<object>;
    // }
    type t('jsData) = {
      data: Js.nullable('jsData),
      error: option(ApolloError.Js_.t),
      loading: bool,
      called: bool,
      client: option(ApolloClient.Js_.t),
    };
  };

  type t('data) = {
    data: option('data),
    error: option(ApolloError.t),
    loading: bool,
    called: bool,
    client: option(ApolloClient.t),
  };

  let fromJs: (Js_.t('jsData), ~parse: 'jsData => 'data) => t('data) =
    (js, ~parse) => {
      data: js.data->Js.toOption->Belt.Option.map(parse),
      error: js.error->Belt.Option.map(ApolloError.fromJs),
      loading: js.loading,
      called: js.called,
      client: js.client,
    };
};

module MutationFunctionOptions = {
  module Js_ = {
    // export interface MutationFunctionOptions<TData = any, TVariables = OperationVariables> {
    //     variables?: TVariables;
    //     optimisticResponse?: TData | ((vars: TVariables | {}) => TData);
    //     refetchQueries?: Array<string | PureQueryOptions> | RefetchQueriesFunction;
    //     awaitRefetchQueries?: boolean;
    //     update?: MutationUpdaterFn<TData>;
    //     context?: Context;
    //     fetchPolicy?: WatchQueryFetchPolicy;
    // }
    /**
     * We use deriving abstract here because this is used in a context where passing in explicit
     * properties could override one already passed in
     */
    type t('jsData, 'jsVariables) = {
      // We don't allow optional variables because it's not typesafe
      variables: 'jsVariables,
      optimisticResponse: option((. 'jsVariables) => 'jsData),
      refetchQueries: option(RefetchQueryDescription.Js_.t),
      awaitRefetchQueries: option(bool),
      update: option(MutationUpdaterFn.Js_.t('jsData)),
      context: option(Js.Json.t), // actual: option(Context)
      fetchPolicy: option(WatchQueryFetchPolicy.Js_.t),
    };
  };

  type t('data, 'jsVariables) = {
    variables: 'jsVariables,
    optimisticResponse: option('jsVariables => 'data),
    refetchQueries: option(RefetchQueryDescription.t),
    awaitRefetchQueries: option(bool),
    update: option(MutationUpdaterFn.t('data)),
    context: option(Js.Json.t), // actual: option(Context)
    fetchPolicy: option(WatchQueryFetchPolicy.t),
  };

  let toJs:
    (
      t('data, 'jsVariables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData
    ) =>
    Js_.t('jsData, 'jsVariables) =
    (t, ~parse, ~serialize) => {
      variables: t.variables,
      optimisticResponse:
        t.optimisticResponse
        ->Belt.Option.map(optimisticResponse =>
            (. variables) => optimisticResponse(variables)->serialize
          ),
      refetchQueries:
        t.refetchQueries->Belt.Option.map(RefetchQueryDescription.toJs),
      awaitRefetchQueries: t.awaitRefetchQueries,
      update: t.update->Belt.Option.map(MutationUpdaterFn.toJs(~parse)),
      context: t.context,
      fetchPolicy: t.fetchPolicy->Belt.Option.map(WatchQueryFetchPolicy.toJs),
    };
};

module MutationTuple = {
  module Js_ = {
    // export declare type MutationTuple<TData, TVariables> = [(options?: MutationFunctionOptions<TData, TVariables>) => Promise<FetchResult<TData>>, MutationResult<TData>];
    type t('jsData, 'jsVariables) = (
      option(MutationFunctionOptions.Js_.t('jsData, 'jsVariables)) =>
      Js.Promise.t(FetchResult.Js_.t('jsData)),
      MutationResult.Js_.t('jsData),
    );
  };
  type t_mutationFn('data, 'variables, 'jsVariables) =
    (
      ~awaitRefetchQueries: bool=?,
      ~context: Js.Json.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      ~mapJsVariables: 'jsVariables => 'jsVariables=?,
      ~optimisticResponse: 'jsVariables => 'data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~update: MutationUpdaterFn.t('data)=?,
      'variables
    ) =>
    Js.Promise.t(FetchResult.t('data));

  type t('data, 'variables, 'jsVariables) = (
    t_mutationFn('data, 'variables, 'jsVariables),
    MutationResult.t('data),
  );

  let fromJs:
    (
      Js_.t('jsData, 'jsVariables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData,
      ~serializeVariables: 'variables => 'jsVariables
    ) =>
    t('data, 'variables, 'jsVariables) =
    (
      (jsMutationFn, jsMutationResult),
      ~parse,
      ~serialize,
      ~serializeVariables,
    ) => {
      let mutationFn =
          (
            ~awaitRefetchQueries=?,
            ~context=?,
            ~fetchPolicy=?,
            ~mapJsVariables=Utils.identity,
            ~optimisticResponse=?,
            ~refetchQueries=?,
            ~update=?,
            variables,
          ) => {
        jsMutationFn(
          Some(
            MutationFunctionOptions.toJs(
              {
                variables: variables->serializeVariables->mapJsVariables,
                optimisticResponse,
                refetchQueries,
                awaitRefetchQueries,
                update,
                context,
                fetchPolicy,
              },
              ~parse,
              ~serialize,
            ),
          ),
        )
        ->Js.Promise.then_(
            jsResult =>
              FetchResult.fromJs(jsResult, ~parse)->Js.Promise.resolve,
            _,
          );
      };

      (mutationFn, jsMutationResult->MutationResult.fromJs(~parse));
    };
};

module MutationTuple__noVariables = {
  module Js_ = {
    type t('jsData, 'jsVariables) =
      MutationTuple.Js_.t('jsData, 'jsVariables);
  };

  type t_mutationFn('data, 'jsVariables) =
    (
      ~optimisticResponse: 'jsVariables => 'data=?,
      ~refetchQueries: RefetchQueryDescription.t=?,
      ~awaitRefetchQueries: bool=?,
      ~update: MutationUpdaterFn.t('data)=?,
      ~context: Js.Json.t=?,
      ~fetchPolicy: WatchQueryFetchPolicy.t=?,
      unit
    ) =>
    Js.Promise.t(FetchResult.t('data));

  type t('data, 'jsVariables) = (
    t_mutationFn('data, 'jsVariables),
    MutationResult.t('data),
  );

  let fromJs:
    (
      Js_.t('jsData, 'jsVariables),
      ~parse: 'jsData => 'data,
      ~serialize: 'data => 'jsData,
      ~variables: 'jsVariables
    ) =>
    t('data, 'jsVariables) =
    ((jsMutationFn, jsMutationResult), ~parse, ~serialize, ~variables) => {
      let mutationFn =
          (
            ~optimisticResponse=?,
            ~refetchQueries=?,
            ~awaitRefetchQueries=?,
            ~update=?,
            ~context=?,
            ~fetchPolicy=?,
            (),
          ) => {
        jsMutationFn(
          Some(
            MutationFunctionOptions.toJs(
              {
                variables,
                optimisticResponse,
                refetchQueries,
                awaitRefetchQueries,
                update,
                context,
                fetchPolicy,
              },
              ~parse,
              ~serialize,
            ),
          ),
        )
        ->Js.Promise.then_(
            jsResult =>
              FetchResult.fromJs(jsResult, ~parse)->Js.Promise.resolve,
            _,
          );
      };

      (mutationFn, jsMutationResult->MutationResult.fromJs(~parse));
    };
};

module SubscriptionResult = {
  module Js_ = {
    // export interface SubscriptionResult<TData = any> {
    //     loading: boolean;
    //     data?: TData;
    //     error?: ApolloError;
    // }
    type t('jsData) = {
      loading: bool,
      data: option('jsData),
      error: option(ApolloError.Js_.t),
    };
  };

  type t('data) = {
    loading: bool,
    data: option('data),
    error: option(ApolloError.t),
  };

  let fromJs: (Js_.t('jsData), ~parse: 'jsData => 'data) => t('data) =
    (js, ~parse) => {
      loading: js.loading,
      data: js.data->Belt.Option.map(parse),
      error: js.error->Belt.Option.map(ApolloError.fromJs),
    };
};

module OnSubscriptionDataOptions = {
  module Js_ = {
    // export interface OnSubscriptionDataOptions<TData = any> {
    //     client: ApolloClient<object>;
    //     subscriptionData: SubscriptionResult<TData>;
    // }
    type t('jsData) = {
      client: ApolloClient.t,
      subscriptionData: SubscriptionResult.Js_.t('jsData),
    };
  };

  type t('data) = {
    client: ApolloClient.t,
    subscriptionData: SubscriptionResult.t('data),
  };

  let fromJs: (Js_.t('jsData), ~parse: 'jsData => 'data) => t('data) =
    (js, ~parse) => {
      client: js.client,
      subscriptionData:
        js.subscriptionData->SubscriptionResult.fromJs(~parse),
    };
};

module BaseSubscriptionOptions = {
  module Js_ = {
    // export interface BaseSubscriptionOptions<TData = any, TVariables = OperationVariables> {
    //     variables?: TVariables;
    //     fetchPolicy?: FetchPolicy;
    //     shouldResubscribe?: boolean | ((options: BaseSubscriptionOptions<TData, TVariables>) => boolean);
    //     client?: ApolloClient<object>;
    //     skip?: boolean;
    //     onSubscriptionData?: (options: OnSubscriptionDataOptions<TData>) => any;
    //     onSubscriptionComplete?: () => void;
    // }
    type t('jsData, 'jsVariables) = {
      variables: option('jsVariables),
      fetchPolicy: option(FetchPolicy.t),
      shouldResubscribe: option((. t('jsData, 'jsVariables)) => bool),
      client: option(ApolloClient.t),
      skip: option(bool),
      onSubscriptionData:
        option((. OnSubscriptionDataOptions.Js_.t('jsData)) => unit),
      onSubscriptionComplete: option(unit => unit),
    };
  };

  type t('data, 'jsVariables) = {
    variables: option('jsVariables),
    fetchPolicy: option(FetchPolicy.t),
    shouldResubscribe: option(t('data, 'jsVariables) => bool),
    client: option(ApolloClient.t),
    skip: option(bool),
    onSubscriptionData: option(OnSubscriptionDataOptions.t('data) => unit),
    onSubscriptionComplete: option(unit => unit),
  };

  let fromJs: Js_.t('jsData, 'jsVariables) => t('data, 'jsVariables) =
    js => {
      variables: js.variables,
      fetchPolicy: js.fetchPolicy,
      // shouldResubscribe: what to do here?
      shouldResubscribe: Obj.magic(js.shouldResubscribe),
      client: js.client,
      skip: js.skip,
      // onSubscriptionData: what to do here?
      onSubscriptionData: Obj.magic(js.onSubscriptionData),
      onSubscriptionComplete: js.onSubscriptionComplete,
    };
};

module SubscriptionHookOptions = {
  module Js_ = {
    // export interface SubscriptionHookOptions<TData = any, TVariables = OperationVariables> extends BaseSubscriptionOptions<TData, TVariables> {
    //     subscription?: DocumentNode;
    // }
    type t('jsData, 'jsVariables) = {
      subscription: option(Graphql.documentNode),
      // ...extends BaseSubscriptionOptions
      // Intentionally restricted to not be non-optional. `option(unit)` does not compile cleanly to `undefined`
      variables: 'jsVariables,
      fetchPolicy: option(FetchPolicy.t),
      shouldResubscribe:
        option(
          (. BaseSubscriptionOptions.Js_.t('jsData, 'jsVariables)) => bool,
        ),
      client: option(ApolloClient.t),
      skip: option(bool),
      onSubscriptionData:
        option((. OnSubscriptionDataOptions.Js_.t('jsData)) => unit),
      onSubscriptionComplete: option(unit => unit),
    };
  };

  type t('data, 'jsVariables) = {
    subscription: option(Graphql.documentNode),
    variables: 'jsVariables,
    fetchPolicy: option(FetchPolicy.t),
    shouldResubscribe:
      option(BaseSubscriptionOptions.t('data, 'jsVariables) => bool),
    client: option(ApolloClient.t),
    skip: option(bool),
    onSubscriptionData: option(OnSubscriptionDataOptions.t('data) => unit),
    onSubscriptionComplete: option(unit => unit),
  };

  let toJs:
    (t('data, 'jsVariables), ~parse: 'jsData => 'data) =>
    Js_.t('jsData, 'jsVariables) =
    (t, ~parse) => {
      subscription: t.subscription,
      variables: t.variables,
      fetchPolicy: t.fetchPolicy,
      shouldResubscribe:
        t.shouldResubscribe
        ->Belt.Option.map(shouldResubscribe =>
            (. jsBaseSubscriptionOptions) =>
              shouldResubscribe(
                jsBaseSubscriptionOptions->BaseSubscriptionOptions.fromJs,
              )
          ),
      client: t.client,
      skip: t.skip,
      onSubscriptionData:
        t.onSubscriptionData
        ->Belt.Option.map(onSubscriptionData =>
            (. jsOnSubscriptionDataOptions) =>
              onSubscriptionData(
                jsOnSubscriptionDataOptions->OnSubscriptionDataOptions.fromJs(
                  ~parse,
                ),
              )
          ),
      onSubscriptionComplete: t.onSubscriptionComplete,
    };
};
