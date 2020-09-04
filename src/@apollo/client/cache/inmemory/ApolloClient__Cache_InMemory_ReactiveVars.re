module ReactiveVar = {
  type t('value) = (~newValue: 'value=?, unit) => 'value;

  module Js_ = {
    type nonrec t('value) = t('value);
  };
};

module Js_ = {
  [@bs.module "@apollo/client"]
  external makeVar: 'value => ReactiveVar.Js_.t('value) = "makeVar";
};

let makeVar: 'value => ReactiveVar.t('value) = Js_.makeVar;
